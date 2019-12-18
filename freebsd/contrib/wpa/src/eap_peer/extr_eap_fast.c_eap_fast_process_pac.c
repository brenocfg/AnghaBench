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
struct eap_sm {int expected_failure; } ;
struct eap_peer_config {int /*<<< orphan*/  pac_file; } ;
struct eap_method_ret {int /*<<< orphan*/  methodState; void* decision; } ;
struct eap_fast_pac {int dummy; } ;
struct eap_fast_data {scalar_t__ success; scalar_t__ anon_provisioning; scalar_t__ provisioning; int /*<<< orphan*/  pac; scalar_t__ use_pac_binary_format; int /*<<< orphan*/  max_pac_list_len; int /*<<< orphan*/  current_pac; } ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 void* DECISION_COND_SUCC ; 
 void* DECISION_FAIL ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_fast_add_pac (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct eap_fast_pac*) ; 
 int /*<<< orphan*/  eap_fast_pac_list_truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_fast_process_pac_info (struct eap_fast_pac*) ; 
 scalar_t__ eap_fast_process_pac_tlv (struct eap_fast_pac*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  eap_fast_save_pac (struct eap_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_fast_save_pac_bin (struct eap_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_fast_tlv_pac_ack () ; 
 struct eap_peer_config* eap_get_config (struct eap_sm*) ; 
 int /*<<< orphan*/  os_memset (struct eap_fast_pac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_fast_process_pac(struct eap_sm *sm,
					    struct eap_fast_data *data,
					    struct eap_method_ret *ret,
					    u8 *pac, size_t pac_len)
{
	struct eap_peer_config *config = eap_get_config(sm);
	struct eap_fast_pac entry;

	os_memset(&entry, 0, sizeof(entry));
	if (eap_fast_process_pac_tlv(&entry, pac, pac_len) ||
	    eap_fast_process_pac_info(&entry))
		return NULL;

	eap_fast_add_pac(&data->pac, &data->current_pac, &entry);
	eap_fast_pac_list_truncate(data->pac, data->max_pac_list_len);
	if (data->use_pac_binary_format)
		eap_fast_save_pac_bin(sm, data->pac, config->pac_file);
	else
		eap_fast_save_pac(sm, data->pac, config->pac_file);

	if (data->provisioning) {
		if (data->anon_provisioning) {
			/*
			 * Unauthenticated provisioning does not provide keying
			 * material and must end with an EAP-Failure.
			 * Authentication will be done separately after this.
			 */
			data->success = 0;
			ret->decision = DECISION_FAIL;
		} else {
			/*
			 * Server may or may not allow authenticated
			 * provisioning also for key generation.
			 */
			ret->decision = DECISION_COND_SUCC;
		}
		wpa_printf(MSG_DEBUG, "EAP-FAST: Send PAC-Acknowledgement TLV "
			   "- Provisioning completed successfully");
		sm->expected_failure = 1;
	} else {
		/*
		 * This is PAC refreshing, i.e., normal authentication that is
		 * expected to be completed with an EAP-Success. However,
		 * RFC 5422, Section 3.5 allows EAP-Failure to be sent even
		 * after protected success exchange in case of EAP-Fast
		 * provisioning, so we better use DECISION_COND_SUCC here
		 * instead of DECISION_UNCOND_SUCC.
		 */
		wpa_printf(MSG_DEBUG, "EAP-FAST: Send PAC-Acknowledgement TLV "
			   "- PAC refreshing completed successfully");
		ret->decision = DECISION_COND_SUCC;
	}
	ret->methodState = METHOD_DONE;
	return eap_fast_tlv_pac_ack();
}