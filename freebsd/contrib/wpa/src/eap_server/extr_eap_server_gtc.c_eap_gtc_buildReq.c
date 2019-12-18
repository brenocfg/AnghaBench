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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_gtc_data {int /*<<< orphan*/  state; scalar_t__ prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTINUE ; 
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_TYPE_GTC ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t os_strlen (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_gtc_buildReq(struct eap_sm *sm, void *priv, u8 id)
{
	struct eap_gtc_data *data = priv;
	struct wpabuf *req;
	char *msg;
	size_t msg_len;

	msg = data->prefix ? "CHALLENGE=Password" : "Password";

	msg_len = os_strlen(msg);
	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_GTC, msg_len,
			    EAP_CODE_REQUEST, id);
	if (req == NULL) {
		wpa_printf(MSG_ERROR, "EAP-GTC: Failed to allocate memory for "
			   "request");
		data->state = FAILURE;
		return NULL;
	}

	wpabuf_put_data(req, msg, msg_len);

	data->state = CONTINUE;

	return req;
}