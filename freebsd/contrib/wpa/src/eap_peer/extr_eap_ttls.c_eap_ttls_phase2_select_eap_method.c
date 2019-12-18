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
struct eap_ttls_data {size_t num_phase2_eap_types; TYPE_2__ phase2_eap_type; TYPE_1__* phase2_eap_types; } ;
struct TYPE_3__ {scalar_t__ vendor; scalar_t__ method; } ;

/* Variables and functions */
 scalar_t__ EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void eap_ttls_phase2_select_eap_method(struct eap_ttls_data *data,
					      u8 method)
{
	size_t i;
	for (i = 0; i < data->num_phase2_eap_types; i++) {
		if (data->phase2_eap_types[i].vendor != EAP_VENDOR_IETF ||
		    data->phase2_eap_types[i].method != method)
			continue;

		data->phase2_eap_type.vendor =
			data->phase2_eap_types[i].vendor;
		data->phase2_eap_type.method =
			data->phase2_eap_types[i].method;
		wpa_printf(MSG_DEBUG, "EAP-TTLS: Selected "
			   "Phase 2 EAP vendor %d method %d",
			   data->phase2_eap_type.vendor,
			   data->phase2_eap_type.method);
		break;
	}
}