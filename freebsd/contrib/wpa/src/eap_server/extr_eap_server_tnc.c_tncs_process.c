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
struct wpabuf {int dummy; } ;
struct eap_tnc_data {int /*<<< orphan*/  recommendation; int /*<<< orphan*/  tncs; } ;
typedef  enum tncs_process_res { ____Placeholder_tncs_process_res } tncs_process_res ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW ; 
 int /*<<< orphan*/  FAIL ; 
 int /*<<< orphan*/  ISOLATE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  NO_ACCESS ; 
 int /*<<< orphan*/  NO_RECOMMENDATION ; 
 int /*<<< orphan*/  RECOMMENDATION ; 
#define  TNCCS_PROCESS_ERROR 132 
#define  TNCCS_RECOMMENDATION_ALLOW 131 
#define  TNCCS_RECOMMENDATION_ISOLATE 130 
#define  TNCCS_RECOMMENDATION_NO_ACCESS 129 
#define  TNCCS_RECOMMENDATION_NO_RECOMMENDATION 128 
 int /*<<< orphan*/  eap_tnc_set_state (struct eap_tnc_data*,int /*<<< orphan*/ ) ; 
 int tncs_process_if_tnccs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static void tncs_process(struct eap_tnc_data *data, struct wpabuf *inbuf)
{
	enum tncs_process_res res;

	res = tncs_process_if_tnccs(data->tncs, wpabuf_head(inbuf),
				    wpabuf_len(inbuf));
	switch (res) {
	case TNCCS_RECOMMENDATION_ALLOW:
		wpa_printf(MSG_DEBUG, "EAP-TNC: TNCS allowed access");
		eap_tnc_set_state(data, RECOMMENDATION);
		data->recommendation = ALLOW;
		break;
	case TNCCS_RECOMMENDATION_NO_RECOMMENDATION:
		wpa_printf(MSG_DEBUG, "EAP-TNC: TNCS has no recommendation");
		eap_tnc_set_state(data, RECOMMENDATION);
		data->recommendation = NO_RECOMMENDATION;
		break;
	case TNCCS_RECOMMENDATION_ISOLATE:
		wpa_printf(MSG_DEBUG, "EAP-TNC: TNCS requested isolation");
		eap_tnc_set_state(data, RECOMMENDATION);
		data->recommendation = ISOLATE;
		break;
	case TNCCS_RECOMMENDATION_NO_ACCESS:
		wpa_printf(MSG_DEBUG, "EAP-TNC: TNCS rejected access");
		eap_tnc_set_state(data, RECOMMENDATION);
		data->recommendation = NO_ACCESS;
		break;
	case TNCCS_PROCESS_ERROR:
		wpa_printf(MSG_DEBUG, "EAP-TNC: TNCS processing error");
		eap_tnc_set_state(data, FAIL);
		break;
	default:
		break;
	}
}