#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {TYPE_1__* user; } ;
struct eap_pax_hdr {int op_code; } ;
struct eap_pax_data {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/ * password; } ;

/* Variables and functions */
#define  EAP_PAX_OP_ACK 129 
#define  EAP_PAX_OP_STD_2 128 
 int /*<<< orphan*/  EAP_TYPE_PAX ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  eap_pax_process_ack (struct eap_sm*,struct eap_pax_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  eap_pax_process_std_2 (struct eap_sm*,struct eap_pax_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_pax_process(struct eap_sm *sm, void *priv,
			    struct wpabuf *respData)
{
	struct eap_pax_data *data = priv;
	struct eap_pax_hdr *resp;
	const u8 *pos;
	size_t len;

	if (sm->user == NULL || sm->user->password == NULL) {
		wpa_printf(MSG_INFO, "EAP-PAX: Plaintext password not "
			   "configured");
		data->state = FAILURE;
		return;
	}

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_PAX, respData, &len);
	if (pos == NULL || len < sizeof(*resp))
		return;

	resp = (struct eap_pax_hdr *) pos;

	switch (resp->op_code) {
	case EAP_PAX_OP_STD_2:
		eap_pax_process_std_2(sm, data, respData);
		break;
	case EAP_PAX_OP_ACK:
		eap_pax_process_ack(sm, data, respData);
		break;
	}
}