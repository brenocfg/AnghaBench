#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__ vendor; scalar_t__ method; } ;
struct eap_fast_data {size_t num_phase2_types; TYPE_2__ phase2_type; TYPE_1__* phase2_types; scalar_t__ anon_provisioning; } ;
struct TYPE_3__ {scalar_t__ vendor; scalar_t__ method; } ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_MSCHAPV2 ; 
 scalar_t__ EAP_TYPE_NONE ; 
 scalar_t__ EAP_TYPE_TNC ; 
 scalar_t__ EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 

__attribute__((used)) static int eap_fast_select_phase2_method(struct eap_fast_data *data, u8 type)
{
	size_t i;

	/* TODO: TNC with anonymous provisioning; need to require both
	 * completed MSCHAPv2 and TNC */

	if (data->anon_provisioning && type != EAP_TYPE_MSCHAPV2) {
		wpa_printf(MSG_INFO, "EAP-FAST: Only EAP-MSCHAPv2 is allowed "
			   "during unauthenticated provisioning; reject phase2"
			   " type %d", type);
		return -1;
	}

#ifdef EAP_TNC
	if (type == EAP_TYPE_TNC) {
		data->phase2_type.vendor = EAP_VENDOR_IETF;
		data->phase2_type.method = EAP_TYPE_TNC;
		wpa_printf(MSG_DEBUG, "EAP-FAST: Selected Phase 2 EAP "
			   "vendor %d method %d for TNC",
			   data->phase2_type.vendor,
			   data->phase2_type.method);
		return 0;
	}
#endif /* EAP_TNC */

	for (i = 0; i < data->num_phase2_types; i++) {
		if (data->phase2_types[i].vendor != EAP_VENDOR_IETF ||
		    data->phase2_types[i].method != type)
			continue;

		data->phase2_type.vendor = data->phase2_types[i].vendor;
		data->phase2_type.method = data->phase2_types[i].method;
		wpa_printf(MSG_DEBUG, "EAP-FAST: Selected Phase 2 EAP "
			   "vendor %d method %d",
			   data->phase2_type.vendor,
			   data->phase2_type.method);
		break;
	}

	if (type != data->phase2_type.method || type == EAP_TYPE_NONE)
		return -1;

	return 0;
}