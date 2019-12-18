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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_vendor_test_data {scalar_t__ state; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 scalar_t__ CONFIRM ; 
 int /*<<< orphan*/  EAP_VENDOR_ID ; 
 int /*<<< orphan*/  EAP_VENDOR_TYPE ; 
 scalar_t__ FAILURE ; 
 scalar_t__ INIT ; 
 scalar_t__ SUCCESS ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  eap_vendor_test_state (struct eap_vendor_test_data*,scalar_t__) ; 

__attribute__((used)) static void eap_vendor_test_process(struct eap_sm *sm, void *priv,
				    struct wpabuf *respData)
{
	struct eap_vendor_test_data *data = priv;
	const u8 *pos;
	size_t len;

	pos = eap_hdr_validate(EAP_VENDOR_ID, EAP_VENDOR_TYPE, respData, &len);
	if (pos == NULL || len < 1)
		return;

	if (data->state == INIT) {
		if (*pos == 2)
			eap_vendor_test_state(data, CONFIRM);
		else
			eap_vendor_test_state(data, FAILURE);
	} else if (data->state == CONFIRM) {
		if (*pos == 4)
			eap_vendor_test_state(data, SUCCESS);
		else
			eap_vendor_test_state(data, FAILURE);
	} else
		eap_vendor_test_state(data, FAILURE);
}