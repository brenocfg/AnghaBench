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
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_NOTIFICATION ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA_EVENT_EAP_NOTIFICATION ; 
 scalar_t__* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,size_t*) ; 
 scalar_t__ isprint (scalar_t__ const) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_sm_processNotify(struct eap_sm *sm, const struct wpabuf *req)
{
	const u8 *pos;
	char *msg;
	size_t i, msg_len;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_NOTIFICATION, req,
			       &msg_len);
	if (pos == NULL)
		return;
	wpa_hexdump_ascii(MSG_DEBUG, "EAP: EAP-Request Notification data",
			  pos, msg_len);

	msg = os_malloc(msg_len + 1);
	if (msg == NULL)
		return;
	for (i = 0; i < msg_len; i++)
		msg[i] = isprint(pos[i]) ? (char) pos[i] : '_';
	msg[msg_len] = '\0';
	wpa_msg(sm->msg_ctx, MSG_INFO, "%s%s",
		WPA_EVENT_EAP_NOTIFICATION, msg);
	os_free(msg);
}