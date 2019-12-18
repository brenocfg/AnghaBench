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
struct eap_sm {int /*<<< orphan*/  msg_ctx; } ;
struct eap_peer_config {int mschapv2_retry; int /*<<< orphan*/ * new_password; scalar_t__ phase2; } ;
struct eap_mschapv2_data {int passwd_change_challenge_valid; int passwd_change_version; void* prev_error; int /*<<< orphan*/  passwd_change_challenge; } ;

/* Variables and functions */
 void* ERROR_AUTHENTICATION_FAILURE ; 
 void* ERROR_PASSWD_EXPIRED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int PASSWD_CHANGE_CHAL_LEN ; 
 void* atoi (char*) ; 
 struct eap_peer_config* eap_get_config (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_request_identity (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_request_new_password (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_request_password (struct eap_sm*) ; 
 scalar_t__ hexstr2bin (char*,int /*<<< orphan*/ ,int) ; 
 char* os_strchr (char*,char) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 scalar_t__ os_strstr (scalar_t__,char*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_mschapv2_failure_txt(struct eap_sm *sm,
				    struct eap_mschapv2_data *data, char *txt)
{
	char *pos, *msg = "";
	int retry = 1;
	struct eap_peer_config *config = eap_get_config(sm);

	/* For example:
	 * E=691 R=1 C=<32 octets hex challenge> V=3 M=Authentication Failure
	 */

	pos = txt;

	if (pos && os_strncmp(pos, "E=", 2) == 0) {
		pos += 2;
		data->prev_error = atoi(pos);
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: error %d",
			   data->prev_error);
		pos = os_strchr(pos, ' ');
		if (pos)
			pos++;
	}

	if (pos && os_strncmp(pos, "R=", 2) == 0) {
		pos += 2;
		retry = atoi(pos);
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: retry is %sallowed",
			   retry == 1 ? "" : "not ");
		pos = os_strchr(pos, ' ');
		if (pos)
			pos++;
	}

	if (pos && os_strncmp(pos, "C=", 2) == 0) {
		int hex_len;
		pos += 2;
		hex_len = os_strchr(pos, ' ') - (char *) pos;
		if (hex_len == PASSWD_CHANGE_CHAL_LEN * 2) {
			if (hexstr2bin(pos, data->passwd_change_challenge,
				       PASSWD_CHANGE_CHAL_LEN)) {
				wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: invalid "
					   "failure challenge");
			} else {
				wpa_hexdump(MSG_DEBUG, "EAP-MSCHAPV2: failure "
					    "challenge",
					    data->passwd_change_challenge,
					    PASSWD_CHANGE_CHAL_LEN);
				data->passwd_change_challenge_valid = 1;
			}
		} else {
			wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: invalid failure "
				   "challenge len %d", hex_len);
		}
		pos = os_strchr(pos, ' ');
		if (pos)
			pos++;
	} else {
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: required challenge field "
			   "was not present in failure message");
	}

	if (pos && os_strncmp(pos, "V=", 2) == 0) {
		pos += 2;
		data->passwd_change_version = atoi(pos);
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: password changing "
			   "protocol version %d", data->passwd_change_version);
		pos = os_strchr(pos, ' ');
		if (pos)
			pos++;
	}

	if (pos && os_strncmp(pos, "M=", 2) == 0) {
		pos += 2;
		msg = pos;
	}
	if (data->prev_error == ERROR_AUTHENTICATION_FAILURE && retry &&
	    config && config->phase2 &&
	    os_strstr(config->phase2, "mschapv2_retry=0")) {
		wpa_printf(MSG_DEBUG,
			   "EAP-MSCHAPV2: mark password retry disabled based on local configuration");
		retry = 0;
	}
	wpa_msg(sm->msg_ctx, MSG_WARNING,
		"EAP-MSCHAPV2: failure message: '%s' (retry %sallowed, error "
		"%d)",
		msg, retry == 1 ? "" : "not ", data->prev_error);
	if (data->prev_error == ERROR_PASSWD_EXPIRED &&
	    data->passwd_change_version == 3 && config) {
		if (config->new_password == NULL) {
			wpa_msg(sm->msg_ctx, MSG_INFO,
				"EAP-MSCHAPV2: Password expired - password "
				"change required");
			eap_sm_request_new_password(sm);
		}
	} else if (retry == 1 && config) {
		/* TODO: could prevent the current password from being used
		 * again at least for some period of time */
		if (!config->mschapv2_retry)
			eap_sm_request_identity(sm);
		eap_sm_request_password(sm);
		config->mschapv2_retry = 1;
	} else if (config) {
		/* TODO: prevent retries using same username/password */
		config->mschapv2_retry = 0;
	}

	return retry == 1;
}