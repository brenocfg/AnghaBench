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
struct eap_tnc_data {int state; int /*<<< orphan*/  out_used; int /*<<< orphan*/ * out_buf; int /*<<< orphan*/  tncs; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
#define  CONTINUE 134 
#define  DONE 133 
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
#define  FAIL 132 
#define  FRAG_ACK 131 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  RECOMMENDATION 130 
#define  START 129 
#define  WAIT_FRAG_ACK 128 
 int /*<<< orphan*/ * eap_tnc_build (struct eap_sm*,struct eap_tnc_data*) ; 
 struct wpabuf* eap_tnc_build_frag_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_tnc_build_msg (struct eap_tnc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * eap_tnc_build_recommendation (struct eap_sm*,struct eap_tnc_data*) ; 
 struct wpabuf* eap_tnc_build_start (struct eap_sm*,struct eap_tnc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tncs_init_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_tnc_buildReq(struct eap_sm *sm, void *priv, u8 id)
{
	struct eap_tnc_data *data = priv;

	switch (data->state) {
	case START:
		tncs_init_connection(data->tncs);
		return eap_tnc_build_start(sm, data, id);
	case CONTINUE:
		if (data->out_buf == NULL) {
			data->out_buf = eap_tnc_build(sm, data);
			if (data->out_buf == NULL) {
				wpa_printf(MSG_DEBUG, "EAP-TNC: Failed to "
					   "generate message");
				return NULL;
			}
			data->out_used = 0;
		}
		return eap_tnc_build_msg(data, id);
	case RECOMMENDATION:
		if (data->out_buf == NULL) {
			data->out_buf = eap_tnc_build_recommendation(sm, data);
			if (data->out_buf == NULL) {
				wpa_printf(MSG_DEBUG, "EAP-TNC: Failed to "
					   "generate recommendation message");
				return NULL;
			}
			data->out_used = 0;
		}
		return eap_tnc_build_msg(data, id);
	case WAIT_FRAG_ACK:
		return eap_tnc_build_msg(data, id);
	case FRAG_ACK:
		return eap_tnc_build_frag_ack(id, EAP_CODE_REQUEST);
	case DONE:
	case FAIL:
		return NULL;
	}

	return NULL;
}