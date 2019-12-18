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
struct eap_sm {int dummy; } ;
struct eap_hdr {long code; int /*<<< orphan*/  identifier; int /*<<< orphan*/  length; } ;
struct eap_fast_data {int dummy; } ;

/* Variables and functions */
#define  EAP_CODE_RESPONSE 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 size_t be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_fast_process_phase2_response (struct eap_sm*,struct eap_fast_data*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  eap_fast_req_failure (struct eap_sm*,struct eap_fast_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long,...) ; 

__attribute__((used)) static void eap_fast_process_phase2_eap(struct eap_sm *sm,
					struct eap_fast_data *data,
					u8 *in_data, size_t in_len)
{
	struct eap_hdr *hdr;
	size_t len;

	hdr = (struct eap_hdr *) in_data;
	if (in_len < (int) sizeof(*hdr)) {
		wpa_printf(MSG_INFO, "EAP-FAST: Too short Phase 2 "
			   "EAP frame (len=%lu)", (unsigned long) in_len);
		eap_fast_req_failure(sm, data);
		return;
	}
	len = be_to_host16(hdr->length);
	if (len > in_len) {
		wpa_printf(MSG_INFO, "EAP-FAST: Length mismatch in "
			   "Phase 2 EAP frame (len=%lu hdr->length=%lu)",
			   (unsigned long) in_len, (unsigned long) len);
		eap_fast_req_failure(sm, data);
		return;
	}
	wpa_printf(MSG_DEBUG, "EAP-FAST: Received Phase 2: code=%d "
		   "identifier=%d length=%lu", hdr->code, hdr->identifier,
		   (unsigned long) len);
	switch (hdr->code) {
	case EAP_CODE_RESPONSE:
		eap_fast_process_phase2_response(sm, data, (u8 *) hdr, len);
		break;
	default:
		wpa_printf(MSG_INFO, "EAP-FAST: Unexpected code=%d in "
			   "Phase 2 EAP header", hdr->code);
		break;
	}
}