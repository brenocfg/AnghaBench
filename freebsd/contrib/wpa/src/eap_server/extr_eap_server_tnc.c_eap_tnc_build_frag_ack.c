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

/* Variables and functions */
 int /*<<< orphan*/  EAP_TNC_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_TNC ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_tnc_build_frag_ack(u8 id, u8 code)
{
	struct wpabuf *msg;

	msg = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_TNC, 1, code, id);
	if (msg == NULL) {
		wpa_printf(MSG_ERROR, "EAP-TNC: Failed to allocate memory "
			   "for fragment ack");
		return NULL;
	}
	wpabuf_put_u8(msg, EAP_TNC_VERSION); /* Flags */

	wpa_printf(MSG_DEBUG, "EAP-TNC: Send fragment ack");

	return msg;
}