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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_eke_data {int dummy; } ;

/* Variables and functions */
#define  EAP_EKE_COMMIT 131 
#define  EAP_EKE_CONFIRM 130 
#define  EAP_EKE_FAILURE 129 
#define  EAP_EKE_ID 128 
 int /*<<< orphan*/  EAP_TYPE_EKE ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_eke_process_commit (struct eap_sm*,struct eap_eke_data*,struct wpabuf*,int const*,int) ; 
 int /*<<< orphan*/  eap_eke_process_confirm (struct eap_sm*,struct eap_eke_data*,struct wpabuf*,int const*,int) ; 
 int /*<<< orphan*/  eap_eke_process_failure (struct eap_sm*,struct eap_eke_data*,struct wpabuf*,int const*,int) ; 
 int /*<<< orphan*/  eap_eke_process_identity (struct eap_sm*,struct eap_eke_data*,struct wpabuf*,int const*,int) ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int) ; 

__attribute__((used)) static void eap_eke_process(struct eap_sm *sm, void *priv,
			     struct wpabuf *respData)
{
	struct eap_eke_data *data = priv;
	u8 eke_exch;
	size_t len;
	const u8 *pos, *end;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_EKE, respData, &len);
	if (pos == NULL || len < 1)
		return;

	eke_exch = *pos;
	end = pos + len;
	pos++;

	wpa_hexdump(MSG_DEBUG, "EAP-EKE: Received payload", pos, end - pos);

	switch (eke_exch) {
	case EAP_EKE_ID:
		eap_eke_process_identity(sm, data, respData, pos, end - pos);
		break;
	case EAP_EKE_COMMIT:
		eap_eke_process_commit(sm, data, respData, pos, end - pos);
		break;
	case EAP_EKE_CONFIRM:
		eap_eke_process_confirm(sm, data, respData, pos, end - pos);
		break;
	case EAP_EKE_FAILURE:
		eap_eke_process_failure(sm, data, respData, pos, end - pos);
		break;
	}
}