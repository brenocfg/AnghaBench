#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct wpabuf {int dummy; } ;
struct eap_sm {TYPE_2__* user; scalar_t__ eap_sim_aka_result_ind; } ;
struct eap_sim_msg {int dummy; } ;
struct eap_aka_data {scalar_t__ eap_method; int /*<<< orphan*/  k_aut; scalar_t__ network_name_len; int /*<<< orphan*/ * network_name; scalar_t__ kdf; int /*<<< orphan*/ * autn; int /*<<< orphan*/ * rand; } ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {scalar_t__ vendor; scalar_t__ method; } ;

/* Variables and functions */
 scalar_t__ EAP_AKA_AUTN_LEN ; 
 scalar_t__ EAP_AKA_BIDDING_FLAG_D ; 
 scalar_t__ EAP_AKA_PRIME_KDF ; 
 scalar_t__ EAP_AKA_RAND_LEN ; 
 int /*<<< orphan*/  EAP_AKA_SUBTYPE_CHALLENGE ; 
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int EAP_MAX_METHODS ; 
 int /*<<< orphan*/  EAP_SIM_AT_AUTN ; 
 int /*<<< orphan*/  EAP_SIM_AT_BIDDING ; 
 int /*<<< orphan*/  EAP_SIM_AT_KDF ; 
 int /*<<< orphan*/  EAP_SIM_AT_KDF_INPUT ; 
 int /*<<< orphan*/  EAP_SIM_AT_MAC ; 
 int /*<<< orphan*/  EAP_SIM_AT_RAND ; 
 int /*<<< orphan*/  EAP_SIM_AT_RESULT_IND ; 
 scalar_t__ EAP_TYPE_AKA ; 
 scalar_t__ EAP_TYPE_AKA_PRIME ; 
 scalar_t__ EAP_TYPE_NONE ; 
 scalar_t__ EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_aka_add_checkcode (struct eap_aka_data*,struct eap_sim_msg*) ; 
 scalar_t__ eap_aka_build_encr (struct eap_sm*,struct eap_aka_data*,struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  eap_sim_msg_add_mac (struct eap_sim_msg*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_free (struct eap_sim_msg*) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_aka_build_challenge(struct eap_sm *sm,
					       struct eap_aka_data *data,
					       u8 id)
{
	struct eap_sim_msg *msg;

	wpa_printf(MSG_DEBUG, "EAP-AKA: Generating Challenge");
	msg = eap_sim_msg_init(EAP_CODE_REQUEST, id, data->eap_method,
			       EAP_AKA_SUBTYPE_CHALLENGE);
	wpa_printf(MSG_DEBUG, "   AT_RAND");
	eap_sim_msg_add(msg, EAP_SIM_AT_RAND, 0, data->rand, EAP_AKA_RAND_LEN);
	wpa_printf(MSG_DEBUG, "   AT_AUTN");
	eap_sim_msg_add(msg, EAP_SIM_AT_AUTN, 0, data->autn, EAP_AKA_AUTN_LEN);
	if (data->eap_method == EAP_TYPE_AKA_PRIME) {
		if (data->kdf) {
			/* Add the selected KDF into the beginning */
			wpa_printf(MSG_DEBUG, "   AT_KDF");
			eap_sim_msg_add(msg, EAP_SIM_AT_KDF, data->kdf,
					NULL, 0);
		}
		wpa_printf(MSG_DEBUG, "   AT_KDF");
		eap_sim_msg_add(msg, EAP_SIM_AT_KDF, EAP_AKA_PRIME_KDF,
				NULL, 0);
		wpa_printf(MSG_DEBUG, "   AT_KDF_INPUT");
		eap_sim_msg_add(msg, EAP_SIM_AT_KDF_INPUT,
				data->network_name_len,
				data->network_name, data->network_name_len);
	}

	if (eap_aka_build_encr(sm, data, msg, 0, NULL)) {
		eap_sim_msg_free(msg);
		return NULL;
	}

	eap_aka_add_checkcode(data, msg);

	if (sm->eap_sim_aka_result_ind) {
		wpa_printf(MSG_DEBUG, "   AT_RESULT_IND");
		eap_sim_msg_add(msg, EAP_SIM_AT_RESULT_IND, 0, NULL, 0);
	}

#ifdef EAP_SERVER_AKA_PRIME
	if (data->eap_method == EAP_TYPE_AKA) {
		u16 flags = 0;
		int i;
		int aka_prime_preferred = 0;

		i = 0;
		while (sm->user && i < EAP_MAX_METHODS &&
		       (sm->user->methods[i].vendor != EAP_VENDOR_IETF ||
			sm->user->methods[i].method != EAP_TYPE_NONE)) {
			if (sm->user->methods[i].vendor == EAP_VENDOR_IETF) {
				if (sm->user->methods[i].method ==
				    EAP_TYPE_AKA)
					break;
				if (sm->user->methods[i].method ==
				    EAP_TYPE_AKA_PRIME) {
					aka_prime_preferred = 1;
					break;
				}
			}
			i++;
		}

		if (aka_prime_preferred)
			flags |= EAP_AKA_BIDDING_FLAG_D;
		eap_sim_msg_add(msg, EAP_SIM_AT_BIDDING, flags, NULL, 0);
	}
#endif /* EAP_SERVER_AKA_PRIME */

	wpa_printf(MSG_DEBUG, "   AT_MAC");
	eap_sim_msg_add_mac(msg, EAP_SIM_AT_MAC);
	return eap_sim_msg_finish(msg, data->eap_method, data->k_aut, NULL, 0);
}