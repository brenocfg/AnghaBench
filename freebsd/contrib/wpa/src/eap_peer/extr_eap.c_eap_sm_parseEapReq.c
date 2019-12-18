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
typedef  void* u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {void* rxFailure; int /*<<< orphan*/  eap_method_priv; TYPE_1__* m; void* rxSuccess; int /*<<< orphan*/  reqId; void* reqMethod; void* rxResp; int /*<<< orphan*/  selectedMethod; void* reqVendorMethod; int /*<<< orphan*/  reqVendor; void* rxReq; int /*<<< orphan*/  req_sha1; scalar_t__ workaround; } ;
struct eap_hdr {int code; int /*<<< orphan*/  identifier; int /*<<< orphan*/  length; } ;
struct TYPE_2__ {int (* get_error_code ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  EAP_CODE_FAILURE 133 
#define  EAP_CODE_FINISH 132 
#define  EAP_CODE_INITIATE 131 
#define  EAP_CODE_REQUEST 130 
#define  EAP_CODE_RESPONSE 129 
#define  EAP_CODE_SUCCESS 128 
 void* EAP_TYPE_EXPANDED ; 
 int /*<<< orphan*/  EAP_TYPE_LEAP ; 
 void* EAP_TYPE_NONE ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int NO_EAP_METHOD_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  WPA_GET_BE24 (void* const*) ; 
 void* WPA_GET_BE32 (void* const*) ; 
 size_t be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_notify_status (struct eap_sm*,char*,char*) ; 
 int /*<<< orphan*/  eap_peer_finish (struct eap_sm*,struct eap_hdr const*,size_t) ; 
 int /*<<< orphan*/  eap_peer_initiate (struct eap_sm*,struct eap_hdr const*,size_t) ; 
 int /*<<< orphan*/  eap_report_error (struct eap_sm*,int) ; 
 int /*<<< orphan*/  sha1_vector (int,void* const**,size_t*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 void* wpabuf_head (struct wpabuf const*) ; 
 size_t wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static void eap_sm_parseEapReq(struct eap_sm *sm, const struct wpabuf *req)
{
	const struct eap_hdr *hdr;
	size_t plen;
	const u8 *pos;

	sm->rxReq = sm->rxResp = sm->rxSuccess = sm->rxFailure = FALSE;
	sm->reqId = 0;
	sm->reqMethod = EAP_TYPE_NONE;
	sm->reqVendor = EAP_VENDOR_IETF;
	sm->reqVendorMethod = EAP_TYPE_NONE;

	if (req == NULL || wpabuf_len(req) < sizeof(*hdr))
		return;

	hdr = wpabuf_head(req);
	plen = be_to_host16(hdr->length);
	if (plen > wpabuf_len(req)) {
		wpa_printf(MSG_DEBUG, "EAP: Ignored truncated EAP-Packet "
			   "(len=%lu plen=%lu)",
			   (unsigned long) wpabuf_len(req),
			   (unsigned long) plen);
		return;
	}

	sm->reqId = hdr->identifier;

	if (sm->workaround) {
		const u8 *addr[1];
		addr[0] = wpabuf_head(req);
		sha1_vector(1, addr, &plen, sm->req_sha1);
	}

	switch (hdr->code) {
	case EAP_CODE_REQUEST:
		if (plen < sizeof(*hdr) + 1) {
			wpa_printf(MSG_DEBUG, "EAP: Too short EAP-Request - "
				   "no Type field");
			return;
		}
		sm->rxReq = TRUE;
		pos = (const u8 *) (hdr + 1);
		sm->reqMethod = *pos++;
		if (sm->reqMethod == EAP_TYPE_EXPANDED) {
			if (plen < sizeof(*hdr) + 8) {
				wpa_printf(MSG_DEBUG, "EAP: Ignored truncated "
					   "expanded EAP-Packet (plen=%lu)",
					   (unsigned long) plen);
				return;
			}
			sm->reqVendor = WPA_GET_BE24(pos);
			pos += 3;
			sm->reqVendorMethod = WPA_GET_BE32(pos);
		}
		wpa_printf(MSG_DEBUG, "EAP: Received EAP-Request id=%d "
			   "method=%u vendor=%u vendorMethod=%u",
			   sm->reqId, sm->reqMethod, sm->reqVendor,
			   sm->reqVendorMethod);
		break;
	case EAP_CODE_RESPONSE:
		if (sm->selectedMethod == EAP_TYPE_LEAP) {
			/*
			 * LEAP differs from RFC 4137 by using reversed roles
			 * for mutual authentication and because of this, we
			 * need to accept EAP-Response frames if LEAP is used.
			 */
			if (plen < sizeof(*hdr) + 1) {
				wpa_printf(MSG_DEBUG, "EAP: Too short "
					   "EAP-Response - no Type field");
				return;
			}
			sm->rxResp = TRUE;
			pos = (const u8 *) (hdr + 1);
			sm->reqMethod = *pos;
			wpa_printf(MSG_DEBUG, "EAP: Received EAP-Response for "
				   "LEAP method=%d id=%d",
				   sm->reqMethod, sm->reqId);
			break;
		}
		wpa_printf(MSG_DEBUG, "EAP: Ignored EAP-Response");
		break;
	case EAP_CODE_SUCCESS:
		wpa_printf(MSG_DEBUG, "EAP: Received EAP-Success");
		eap_notify_status(sm, "completion", "success");
		sm->rxSuccess = TRUE;
		break;
	case EAP_CODE_FAILURE:
		wpa_printf(MSG_DEBUG, "EAP: Received EAP-Failure");
		eap_notify_status(sm, "completion", "failure");

		/* Get the error code from method */
		if (sm->m && sm->m->get_error_code) {
			int error_code;

			error_code = sm->m->get_error_code(sm->eap_method_priv);
			if (error_code != NO_EAP_METHOD_ERROR)
				eap_report_error(sm, error_code);
		}
		sm->rxFailure = TRUE;
		break;
	case EAP_CODE_INITIATE:
		eap_peer_initiate(sm, hdr, plen);
		break;
	case EAP_CODE_FINISH:
		eap_peer_finish(sm, hdr, plen);
		break;
	default:
		wpa_printf(MSG_DEBUG, "EAP: Ignored EAP-Packet with unknown "
			   "code %d", hdr->code);
		break;
	}
}