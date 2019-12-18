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
typedef  int /*<<< orphan*/  ver ;
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {scalar_t__* identity; scalar_t__ identity_len; } ;
struct eap_sim_msg {int dummy; } ;
struct eap_sim_data {int start_round; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_SIM_AT_ANY_ID_REQ ; 
 int /*<<< orphan*/  EAP_SIM_AT_FULLAUTH_ID_REQ ; 
 int /*<<< orphan*/  EAP_SIM_AT_PERMANENT_ID_REQ ; 
 int /*<<< orphan*/  EAP_SIM_AT_VERSION_LIST ; 
 scalar_t__ EAP_SIM_REAUTH_ID_PREFIX ; 
 int /*<<< orphan*/  EAP_SIM_SUBTYPE_START ; 
 scalar_t__ EAP_SIM_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_SIM ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_free (struct eap_sim_msg*) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_sim_build_start(struct eap_sm *sm,
					   struct eap_sim_data *data, u8 id)
{
	struct eap_sim_msg *msg;
	u8 ver[2];

	wpa_printf(MSG_DEBUG, "EAP-SIM: Generating Start");
	msg = eap_sim_msg_init(EAP_CODE_REQUEST, id, EAP_TYPE_SIM,
			       EAP_SIM_SUBTYPE_START);
	data->start_round++;
	if (data->start_round == 1) {
		/*
		 * RFC 4186, Chap. 4.2.4 recommends that identity from EAP is
		 * ignored and the SIM/Start is used to request the identity.
		 */
		wpa_printf(MSG_DEBUG, "   AT_ANY_ID_REQ");
		eap_sim_msg_add(msg, EAP_SIM_AT_ANY_ID_REQ, 0, NULL, 0);
	} else if (data->start_round > 3) {
		/* Cannot use more than three rounds of Start messages */
		eap_sim_msg_free(msg);
		return NULL;
	} else if (data->start_round == 0) {
		/*
		 * This is a special case that is used to recover from
		 * AT_COUNTER_TOO_SMALL during re-authentication. Since we
		 * already know the identity of the peer, there is no need to
		 * request any identity in this case.
		 */
	} else if (sm->identity && sm->identity_len > 0 &&
		   sm->identity[0] == EAP_SIM_REAUTH_ID_PREFIX) {
		/* Reauth id may have expired - try fullauth */
		wpa_printf(MSG_DEBUG, "   AT_FULLAUTH_ID_REQ");
		eap_sim_msg_add(msg, EAP_SIM_AT_FULLAUTH_ID_REQ, 0, NULL, 0);
	} else {
		wpa_printf(MSG_DEBUG, "   AT_PERMANENT_ID_REQ");
		eap_sim_msg_add(msg, EAP_SIM_AT_PERMANENT_ID_REQ, 0, NULL, 0);
	}
	wpa_printf(MSG_DEBUG, "   AT_VERSION_LIST");
	ver[0] = 0;
	ver[1] = EAP_SIM_VERSION;
	eap_sim_msg_add(msg, EAP_SIM_AT_VERSION_LIST, sizeof(ver),
			ver, sizeof(ver));
	return eap_sim_msg_finish(msg, EAP_TYPE_SIM, NULL, NULL, 0);
}