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
struct eap_sm {scalar_t__* identity; scalar_t__ identity_len; } ;
struct eap_sim_msg {int dummy; } ;
struct eap_aka_data {int identity_round; int /*<<< orphan*/  pending_id; int /*<<< orphan*/  eap_method; } ;

/* Variables and functions */
 scalar_t__ EAP_AKA_PRIME_REAUTH_ID_PREFIX ; 
 scalar_t__ EAP_AKA_REAUTH_ID_PREFIX ; 
 int /*<<< orphan*/  EAP_AKA_SUBTYPE_IDENTITY ; 
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_SIM_AT_ANY_ID_REQ ; 
 int /*<<< orphan*/  EAP_SIM_AT_FULLAUTH_ID_REQ ; 
 int /*<<< orphan*/  EAP_SIM_AT_PERMANENT_ID_REQ ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_aka_add_id_msg (struct eap_aka_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_free (struct eap_sim_msg*) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * eap_aka_build_identity(struct eap_sm *sm,
					      struct eap_aka_data *data, u8 id)
{
	struct eap_sim_msg *msg;
	struct wpabuf *buf;

	wpa_printf(MSG_DEBUG, "EAP-AKA: Generating Identity");
	msg = eap_sim_msg_init(EAP_CODE_REQUEST, id, data->eap_method,
			       EAP_AKA_SUBTYPE_IDENTITY);
	data->identity_round++;
	if (data->identity_round == 1) {
		/*
		 * RFC 4187, Chap. 4.1.4 recommends that identity from EAP is
		 * ignored and the AKA/Identity is used to request the
		 * identity.
		 */
		wpa_printf(MSG_DEBUG, "   AT_ANY_ID_REQ");
		eap_sim_msg_add(msg, EAP_SIM_AT_ANY_ID_REQ, 0, NULL, 0);
	} else if (data->identity_round > 3) {
		/* Cannot use more than three rounds of Identity messages */
		eap_sim_msg_free(msg);
		return NULL;
	} else if (sm->identity && sm->identity_len > 0 &&
		   (sm->identity[0] == EAP_AKA_REAUTH_ID_PREFIX ||
		    sm->identity[0] == EAP_AKA_PRIME_REAUTH_ID_PREFIX)) {
		/* Reauth id may have expired - try fullauth */
		wpa_printf(MSG_DEBUG, "   AT_FULLAUTH_ID_REQ");
		eap_sim_msg_add(msg, EAP_SIM_AT_FULLAUTH_ID_REQ, 0, NULL, 0);
	} else {
		wpa_printf(MSG_DEBUG, "   AT_PERMANENT_ID_REQ");
		eap_sim_msg_add(msg, EAP_SIM_AT_PERMANENT_ID_REQ, 0, NULL, 0);
	}
	buf = eap_sim_msg_finish(msg, data->eap_method, NULL, NULL, 0);
	if (eap_aka_add_id_msg(data, buf) < 0) {
		wpabuf_free(buf);
		return NULL;
	}
	data->pending_id = id;
	return buf;
}