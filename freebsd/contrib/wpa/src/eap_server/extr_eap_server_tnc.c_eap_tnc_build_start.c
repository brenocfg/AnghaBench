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
struct eap_tnc_data {int dummy; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTINUE ; 
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int EAP_TNC_FLAGS_START ; 
 int EAP_TNC_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_TNC ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAIL ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_tnc_set_state (struct eap_tnc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_tnc_build_start(struct eap_sm *sm,
					   struct eap_tnc_data *data, u8 id)
{
	struct wpabuf *req;

	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_TNC, 1, EAP_CODE_REQUEST,
			    id);
	if (req == NULL) {
		wpa_printf(MSG_ERROR, "EAP-TNC: Failed to allocate memory for "
			   "request");
		eap_tnc_set_state(data, FAIL);
		return NULL;
	}

	wpabuf_put_u8(req, EAP_TNC_FLAGS_START | EAP_TNC_VERSION);

	eap_tnc_set_state(data, CONTINUE);

	return req;
}