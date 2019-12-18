#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int init_phase2; } ;
struct eap_peer_config {scalar_t__ pending_req_sim; scalar_t__ pending_req_new_password; scalar_t__ pending_req_otp; scalar_t__ pending_req_password; scalar_t__ pending_req_identity; } ;
struct TYPE_4__ {long method; int /*<<< orphan*/  vendor; } ;
struct eap_peap_data {int phase2_eap_started; int phase2_eap_success; int phase2_success; size_t num_phase2_types; struct wpabuf* pending_phase2_req; int /*<<< orphan*/ * phase2_priv; TYPE_3__* phase2_method; TYPE_1__ phase2_type; TYPE_2__* phase2_types; int /*<<< orphan*/  soh; } ;
struct eap_method_ret {void* methodState; void* decision; } ;
struct eap_hdr {int /*<<< orphan*/  identifier; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  iret ;
struct TYPE_6__ {struct wpabuf* (* process ) (struct eap_sm*,int /*<<< orphan*/ *,struct eap_method_ret*,struct wpabuf*) ;int /*<<< orphan*/ * (* init ) (struct eap_sm*) ;} ;
struct TYPE_5__ {long method; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 void* DECISION_COND_SUCC ; 
 void* DECISION_FAIL ; 
 void* DECISION_UNCOND_SUCC ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
#define  EAP_TYPE_EXPANDED 130 
#define  EAP_TYPE_IDENTITY 129 
 long EAP_TYPE_NONE ; 
#define  EAP_TYPE_TLV 128 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  EAP_VENDOR_MICROSOFT ; 
 void* METHOD_DONE ; 
 void* METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 size_t be_to_host16 (int /*<<< orphan*/ ) ; 
 struct eap_peer_config* eap_get_config (struct eap_sm*) ; 
 long* eap_hdr_validate (int /*<<< orphan*/ ,int,struct wpabuf*,size_t*) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* eap_peer_get_eap_method (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  eap_peer_tls_phase2_nak (TYPE_2__*,size_t,struct eap_hdr*,struct wpabuf**) ; 
 struct wpabuf* eap_sm_buildIdentity (struct eap_sm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eap_tlv_process (struct eap_sm*,struct eap_peap_data*,struct eap_method_ret*,struct wpabuf*,struct wpabuf**,int) ; 
 int /*<<< orphan*/  os_memset (struct eap_method_ret*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * stub1 (struct eap_sm*) ; 
 struct wpabuf* stub2 (struct eap_sm*,int /*<<< orphan*/ *,struct eap_method_ret*,struct wpabuf*) ; 
 struct wpabuf* tncc_process_soh_request (int /*<<< orphan*/ ,long const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc_copy (struct eap_hdr*,size_t) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 struct eap_hdr* wpabuf_mhead (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 

__attribute__((used)) static int eap_peap_phase2_request(struct eap_sm *sm,
				   struct eap_peap_data *data,
				   struct eap_method_ret *ret,
				   struct wpabuf *req,
				   struct wpabuf **resp)
{
	struct eap_hdr *hdr = wpabuf_mhead(req);
	size_t len = be_to_host16(hdr->length);
	u8 *pos;
	struct eap_method_ret iret;
	struct eap_peer_config *config = eap_get_config(sm);

	if (len <= sizeof(struct eap_hdr)) {
		wpa_printf(MSG_INFO, "EAP-PEAP: too short "
			   "Phase 2 request (len=%lu)", (unsigned long) len);
		return -1;
	}
	pos = (u8 *) (hdr + 1);
	wpa_printf(MSG_DEBUG, "EAP-PEAP: Phase 2 Request: type=%d", *pos);
	switch (*pos) {
	case EAP_TYPE_IDENTITY:
		*resp = eap_sm_buildIdentity(sm, hdr->identifier, 1);
		break;
	case EAP_TYPE_TLV:
		os_memset(&iret, 0, sizeof(iret));
		if (eap_tlv_process(sm, data, &iret, req, resp,
				    data->phase2_eap_started &&
				    !data->phase2_eap_success)) {
			ret->methodState = METHOD_DONE;
			ret->decision = DECISION_FAIL;
			return -1;
		}
		if (iret.methodState == METHOD_DONE ||
		    iret.methodState == METHOD_MAY_CONT) {
			ret->methodState = iret.methodState;
			ret->decision = iret.decision;
			data->phase2_success = 1;
		}
		break;
	case EAP_TYPE_EXPANDED:
#ifdef EAP_TNC
		if (data->soh) {
			const u8 *epos;
			size_t eleft;

			epos = eap_hdr_validate(EAP_VENDOR_MICROSOFT, 0x21,
						req, &eleft);
			if (epos) {
				struct wpabuf *buf;
				wpa_printf(MSG_DEBUG,
					   "EAP-PEAP: SoH EAP Extensions");
				buf = tncc_process_soh_request(data->soh,
							       epos, eleft);
				if (buf) {
					*resp = eap_msg_alloc(
						EAP_VENDOR_MICROSOFT, 0x21,
						wpabuf_len(buf),
						EAP_CODE_RESPONSE,
						hdr->identifier);
					if (*resp == NULL) {
						ret->methodState = METHOD_DONE;
						ret->decision = DECISION_FAIL;
						wpabuf_clear_free(buf);
						return -1;
					}
					wpabuf_put_buf(*resp, buf);
					wpabuf_clear_free(buf);
					break;
				}
			}
		}
#endif /* EAP_TNC */
		/* fall through */
	default:
		if (data->phase2_type.vendor == EAP_VENDOR_IETF &&
		    data->phase2_type.method == EAP_TYPE_NONE) {
			size_t i;
			for (i = 0; i < data->num_phase2_types; i++) {
				if (data->phase2_types[i].vendor !=
				    EAP_VENDOR_IETF ||
				    data->phase2_types[i].method != *pos)
					continue;

				data->phase2_type.vendor =
					data->phase2_types[i].vendor;
				data->phase2_type.method =
					data->phase2_types[i].method;
				wpa_printf(MSG_DEBUG, "EAP-PEAP: Selected "
					   "Phase 2 EAP vendor %d method %d",
					   data->phase2_type.vendor,
					   data->phase2_type.method);
				break;
			}
		}
		if (*pos != data->phase2_type.method ||
		    *pos == EAP_TYPE_NONE) {
			if (eap_peer_tls_phase2_nak(data->phase2_types,
						    data->num_phase2_types,
						    hdr, resp))
				return -1;
			return 0;
		}

		if (data->phase2_priv == NULL) {
			data->phase2_method = eap_peer_get_eap_method(
				data->phase2_type.vendor,
				data->phase2_type.method);
			if (data->phase2_method) {
				sm->init_phase2 = 1;
				data->phase2_priv =
					data->phase2_method->init(sm);
				sm->init_phase2 = 0;
			}
		}
		if (data->phase2_priv == NULL || data->phase2_method == NULL) {
			wpa_printf(MSG_INFO, "EAP-PEAP: failed to initialize "
				   "Phase 2 EAP method %d", *pos);
			ret->methodState = METHOD_DONE;
			ret->decision = DECISION_FAIL;
			return -1;
		}
		data->phase2_eap_started = 1;
		os_memset(&iret, 0, sizeof(iret));
		*resp = data->phase2_method->process(sm, data->phase2_priv,
						     &iret, req);
		if ((iret.methodState == METHOD_DONE ||
		     iret.methodState == METHOD_MAY_CONT) &&
		    (iret.decision == DECISION_UNCOND_SUCC ||
		     iret.decision == DECISION_COND_SUCC)) {
			data->phase2_eap_success = 1;
			data->phase2_success = 1;
		}
		break;
	}

	if (*resp == NULL &&
	    (config->pending_req_identity || config->pending_req_password ||
	     config->pending_req_otp || config->pending_req_new_password ||
	     config->pending_req_sim)) {
		wpabuf_clear_free(data->pending_phase2_req);
		data->pending_phase2_req = wpabuf_alloc_copy(hdr, len);
	}

	return 0;
}