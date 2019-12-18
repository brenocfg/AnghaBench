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
struct eap_sm {scalar_t__ identity_len; int /*<<< orphan*/ * identity; } ;
struct eap_sim_attrs {scalar_t__ identity_len; int /*<<< orphan*/  identity; scalar_t__ encr_data; scalar_t__ iv; scalar_t__ mac; } ;
struct eap_aka_data {int pending_id; void* notification; } ;

/* Variables and functions */
 void* EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  NOTIFICATION ; 
 int /*<<< orphan*/  eap_aka_add_id_msg (struct eap_aka_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  eap_aka_determine_identity (struct eap_sm*,struct eap_aka_data*) ; 
 int /*<<< orphan*/  eap_aka_state (struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 int eap_get_id (struct wpabuf*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (scalar_t__) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_aka_process_identity(struct eap_sm *sm,
				     struct eap_aka_data *data,
				     struct wpabuf *respData,
				     struct eap_sim_attrs *attr)
{
	u8 *new_identity;

	wpa_printf(MSG_DEBUG, "EAP-AKA: Processing Identity");

	if (attr->mac || attr->iv || attr->encr_data) {
		wpa_printf(MSG_WARNING, "EAP-AKA: Unexpected attribute "
			   "received in EAP-Response/AKA-Identity");
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}

	/*
	 * We always request identity with AKA/Identity, so the peer is
	 * required to have replied with one.
	 */
	if (!attr->identity || attr->identity_len == 0) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: Peer did not provide any "
			   "identity");
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}

	new_identity = os_malloc(attr->identity_len);
	if (new_identity == NULL) {
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}
	os_free(sm->identity);
	sm->identity = new_identity;
	os_memcpy(sm->identity, attr->identity, attr->identity_len);
	sm->identity_len = attr->identity_len;

	eap_aka_determine_identity(sm, data);
	if (eap_get_id(respData) == data->pending_id) {
		data->pending_id = -1;
		eap_aka_add_id_msg(data, respData);
	}
}