#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rad_handle {int dummy; } ;
struct pam_response {struct pam_response* resp; } ;
struct pam_message {struct pam_response* msg; void* msg_style; } ;
struct pam_conv {int (* conv ) (int,struct pam_message const**,struct pam_response**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  appdata_ptr; } ;
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_CRIT ; 
 int MAX_CHALLENGE_MSGS ; 
 int /*<<< orphan*/  PAM_CONV ; 
 void* PAM_PROMPT_ECHO_ON ; 
 int PAM_SERVICE_ERR ; 
 int PAM_SUCCESS ; 
 void* PAM_TEXT_INFO ; 
#define  RAD_REPLY_MESSAGE 129 
#define  RAD_STATE 128 
 int build_access_request (struct rad_handle*,char const*,struct pam_response*,char const*,char const*,char const*,void const*,size_t) ; 
 int /*<<< orphan*/  free (struct pam_response*) ; 
 int /*<<< orphan*/  memset (struct pam_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pam_get_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const**) ; 
 struct pam_response* rad_cvt_string (void const*,size_t) ; 
 int rad_get_attr (struct rad_handle*,void const**,size_t*) ; 
 int /*<<< orphan*/  rad_strerror (struct rad_handle*) ; 
 struct pam_response* strdup (char*) ; 
 int /*<<< orphan*/  strlen (struct pam_response*) ; 
 int stub1 (int,struct pam_message const**,struct pam_response**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
do_challenge(pam_handle_t *pamh, struct rad_handle *radh, const char *user,
    const char *nas_id, const char *nas_ipaddr, const char *rhost)
{
	int retval;
	int attrtype;
	const void *attrval;
	size_t attrlen;
	const void *state;
	size_t statelen;
	struct pam_message msgs[MAX_CHALLENGE_MSGS];
	const struct pam_message *msg_ptrs[MAX_CHALLENGE_MSGS];
	struct pam_response *resp;
	int num_msgs;
	const void *item;
	const struct pam_conv *conv;

	state = NULL;
	statelen = 0;
	num_msgs = 0;
	while ((attrtype = rad_get_attr(radh, &attrval, &attrlen)) > 0) {
		switch (attrtype) {

		case RAD_STATE:
			state = attrval;
			statelen = attrlen;
			break;

		case RAD_REPLY_MESSAGE:
			if (num_msgs >= MAX_CHALLENGE_MSGS) {
				syslog(LOG_CRIT,
				    "Too many RADIUS challenge messages");
				return (PAM_SERVICE_ERR);
			}
			msgs[num_msgs].msg = rad_cvt_string(attrval, attrlen);
			if (msgs[num_msgs].msg == NULL) {
				syslog(LOG_CRIT,
				    "rad_cvt_string: out of memory");
				return (PAM_SERVICE_ERR);
			}
			msgs[num_msgs].msg_style = PAM_TEXT_INFO;
			msg_ptrs[num_msgs] = &msgs[num_msgs];
			num_msgs++;
			break;
		}
	}
	if (attrtype == -1) {
		syslog(LOG_CRIT, "rad_get_attr: %s", rad_strerror(radh));
		return (PAM_SERVICE_ERR);
	}
	if (num_msgs == 0) {
		msgs[num_msgs].msg = strdup("(null RADIUS challenge): ");
		if (msgs[num_msgs].msg == NULL) {
			syslog(LOG_CRIT, "Out of memory");
			return (PAM_SERVICE_ERR);
		}
		msgs[num_msgs].msg_style = PAM_TEXT_INFO;
		msg_ptrs[num_msgs] = &msgs[num_msgs];
		num_msgs++;
	}
	msgs[num_msgs-1].msg_style = PAM_PROMPT_ECHO_ON;
	if ((retval = pam_get_item(pamh, PAM_CONV, &item)) != PAM_SUCCESS) {
		syslog(LOG_CRIT, "do_challenge: cannot get PAM_CONV");
		return (retval);
	}
	conv = (const struct pam_conv *)item;
	if ((retval = conv->conv(num_msgs, msg_ptrs, &resp,
	    conv->appdata_ptr)) != PAM_SUCCESS)
		return (retval);
	if (build_access_request(radh, user, resp[num_msgs-1].resp, nas_id,
	    nas_ipaddr, rhost, state, statelen) == -1)
		return (PAM_SERVICE_ERR);
	memset(resp[num_msgs-1].resp, 0, strlen(resp[num_msgs-1].resp));
	free(resp[num_msgs-1].resp);
	free(resp);
	while (num_msgs > 0)
		free(msgs[--num_msgs].msg);
	return (PAM_SUCCESS);
}