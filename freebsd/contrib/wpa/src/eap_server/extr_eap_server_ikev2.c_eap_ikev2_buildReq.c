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
struct eap_ikev2_data {int state; int /*<<< orphan*/  out_used; int /*<<< orphan*/ * out_buf; int /*<<< orphan*/  ikev2; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
#define  FRAG_ACK 130 
#define  MSG 129 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  WAIT_FRAG_ACK 128 
 struct wpabuf* eap_ikev2_build_frag_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_ikev2_build_msg (struct eap_ikev2_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ikev2_initiator_build (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_ikev2_buildReq(struct eap_sm *sm, void *priv, u8 id)
{
	struct eap_ikev2_data *data = priv;

	switch (data->state) {
	case MSG:
		if (data->out_buf == NULL) {
			data->out_buf = ikev2_initiator_build(&data->ikev2);
			if (data->out_buf == NULL) {
				wpa_printf(MSG_DEBUG, "EAP-IKEV2: Failed to "
					   "generate IKEv2 message");
				return NULL;
			}
			data->out_used = 0;
		}
		/* fall through */
	case WAIT_FRAG_ACK:
		return eap_ikev2_build_msg(data, id);
	case FRAG_ACK:
		return eap_ikev2_build_frag_ack(id, EAP_CODE_REQUEST);
	default:
		wpa_printf(MSG_DEBUG, "EAP-IKEV2: Unexpected state %d in "
			   "buildReq", data->state);
		return NULL;
	}
}