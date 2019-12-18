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
struct eap_sake_hdr {int subtype; } ;
struct eap_sake_data {int dummy; } ;

/* Variables and functions */
#define  EAP_SAKE_SUBTYPE_AUTH_REJECT 131 
#define  EAP_SAKE_SUBTYPE_CHALLENGE 130 
#define  EAP_SAKE_SUBTYPE_CONFIRM 129 
#define  EAP_SAKE_SUBTYPE_IDENTITY 128 
 int /*<<< orphan*/  EAP_TYPE_SAKE ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  eap_sake_process_auth_reject (struct eap_sm*,struct eap_sake_data*,struct wpabuf*,int const*,int) ; 
 int /*<<< orphan*/  eap_sake_process_challenge (struct eap_sm*,struct eap_sake_data*,struct wpabuf*,int const*,int) ; 
 int /*<<< orphan*/  eap_sake_process_confirm (struct eap_sm*,struct eap_sake_data*,struct wpabuf*,int const*,int) ; 
 int /*<<< orphan*/  eap_sake_process_identity (struct eap_sm*,struct eap_sake_data*,struct wpabuf*,int const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int) ; 

__attribute__((used)) static void eap_sake_process(struct eap_sm *sm, void *priv,
			     struct wpabuf *respData)
{
	struct eap_sake_data *data = priv;
	struct eap_sake_hdr *resp;
	u8 subtype;
	size_t len;
	const u8 *pos, *end;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_SAKE, respData, &len);
	if (pos == NULL || len < sizeof(struct eap_sake_hdr))
		return;

	resp = (struct eap_sake_hdr *) pos;
	end = pos + len;
	subtype = resp->subtype;
	pos = (u8 *) (resp + 1);

	wpa_hexdump(MSG_DEBUG, "EAP-SAKE: Received attributes",
		    pos, end - pos);

	switch (subtype) {
	case EAP_SAKE_SUBTYPE_IDENTITY:
		eap_sake_process_identity(sm, data, respData, pos, end - pos);
		break;
	case EAP_SAKE_SUBTYPE_CHALLENGE:
		eap_sake_process_challenge(sm, data, respData, pos, end - pos);
		break;
	case EAP_SAKE_SUBTYPE_CONFIRM:
		eap_sake_process_confirm(sm, data, respData, pos, end - pos);
		break;
	case EAP_SAKE_SUBTYPE_AUTH_REJECT:
		eap_sake_process_auth_reject(sm, data, respData, pos,
					     end - pos);
		break;
	}
}