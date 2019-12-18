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
struct eap_mschapv2_data {int state; } ;

/* Variables and functions */
#define  CHALLENGE 130 
#define  FAILURE_REQ 129 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  SUCCESS_REQ 128 
 struct wpabuf* eap_mschapv2_build_challenge (struct eap_sm*,struct eap_mschapv2_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_mschapv2_build_failure_req (struct eap_sm*,struct eap_mschapv2_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_mschapv2_build_success_req (struct eap_sm*,struct eap_mschapv2_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct wpabuf * eap_mschapv2_buildReq(struct eap_sm *sm, void *priv,
					     u8 id)
{
	struct eap_mschapv2_data *data = priv;

	switch (data->state) {
	case CHALLENGE:
		return eap_mschapv2_build_challenge(sm, data, id);
	case SUCCESS_REQ:
		return eap_mschapv2_build_success_req(sm, data, id);
	case FAILURE_REQ:
		return eap_mschapv2_build_failure_req(sm, data, id);
	default:
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: Unknown state %d in "
			   "buildReq", data->state);
		break;
	}
	return NULL;
}