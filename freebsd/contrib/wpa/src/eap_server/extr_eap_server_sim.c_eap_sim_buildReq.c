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
struct eap_sm {int dummy; } ;
struct eap_sim_data {int state; } ;

/* Variables and functions */
#define  CHALLENGE 131 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  NOTIFICATION 130 
#define  REAUTH 129 
#define  START 128 
 struct wpabuf* eap_sim_build_challenge (struct eap_sm*,struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_build_notification (struct eap_sm*,struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_build_reauth (struct eap_sm*,struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_build_start (struct eap_sm*,struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct wpabuf * eap_sim_buildReq(struct eap_sm *sm, void *priv, u8 id)
{
	struct eap_sim_data *data = priv;

	switch (data->state) {
	case START:
		return eap_sim_build_start(sm, data, id);
	case CHALLENGE:
		return eap_sim_build_challenge(sm, data, id);
	case REAUTH:
		return eap_sim_build_reauth(sm, data, id);
	case NOTIFICATION:
		return eap_sim_build_notification(sm, data, id);
	default:
		wpa_printf(MSG_DEBUG, "EAP-SIM: Unknown state %d in "
			   "buildReq", data->state);
		break;
	}
	return NULL;
}