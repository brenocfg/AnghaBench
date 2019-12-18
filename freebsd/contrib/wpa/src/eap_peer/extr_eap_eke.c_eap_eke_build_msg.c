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
struct eap_eke_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_TYPE_EKE ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_eke_build_msg(struct eap_eke_data *data, int id,
					 size_t length, u8 eke_exch)
{
	struct wpabuf *msg;
	size_t plen;

	plen = 1 + length;

	msg = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_EKE, plen,
			    EAP_CODE_RESPONSE, id);
	if (msg == NULL) {
		wpa_printf(MSG_ERROR, "EAP-EKE: Failed to allocate memory");
		return NULL;
	}

	wpabuf_put_u8(msg, eke_exch);

	return msg;
}