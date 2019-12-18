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
struct eap_sim_msg {int dummy; } ;
struct eap_sim_attrs {size_t kdf_count; int /*<<< orphan*/ * kdf; } ;
struct eap_aka_data {int /*<<< orphan*/  eap_method; int /*<<< orphan*/  auts; scalar_t__ num_notification; scalar_t__ num_id_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_AKA_AUTS_LEN ; 
 int /*<<< orphan*/  EAP_AKA_SUBTYPE_SYNCHRONIZATION_FAILURE ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_SIM_AT_AUTS ; 
 int /*<<< orphan*/  EAP_SIM_AT_KDF ; 
 int /*<<< orphan*/  EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add_full (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_aka_synchronization_failure(
	struct eap_aka_data *data, u8 id, struct eap_sim_attrs *attr)
{
	struct eap_sim_msg *msg;

	data->num_id_req = 0;
	data->num_notification = 0;

	wpa_printf(MSG_DEBUG, "Generating EAP-AKA Synchronization-Failure "
		   "(id=%d)", id);
	msg = eap_sim_msg_init(EAP_CODE_RESPONSE, id, data->eap_method,
			       EAP_AKA_SUBTYPE_SYNCHRONIZATION_FAILURE);
	wpa_printf(MSG_DEBUG, "   AT_AUTS");
	eap_sim_msg_add_full(msg, EAP_SIM_AT_AUTS, data->auts,
			     EAP_AKA_AUTS_LEN);
	if (data->eap_method == EAP_TYPE_AKA_PRIME) {
		size_t i;

		for (i = 0; i < attr->kdf_count; i++) {
			wpa_printf(MSG_DEBUG, "   AT_KDF");
			eap_sim_msg_add(msg, EAP_SIM_AT_KDF, attr->kdf[i],
					NULL, 0);
		}
	}
	return eap_sim_msg_finish(msg, data->eap_method, NULL, NULL, 0);
}