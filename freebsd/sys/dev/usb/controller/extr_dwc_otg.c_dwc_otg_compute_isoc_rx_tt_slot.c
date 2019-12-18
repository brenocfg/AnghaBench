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
typedef  scalar_t__ uint16_t ;
struct dwc_otg_tt_info {scalar_t__ slot_index; } ;

/* Variables and functions */
 scalar_t__ DWC_OTG_TT_SLOT_MAX ; 

__attribute__((used)) static uint16_t
dwc_otg_compute_isoc_rx_tt_slot(struct dwc_otg_tt_info *pinfo)
{
	if (pinfo->slot_index < DWC_OTG_TT_SLOT_MAX)
		pinfo->slot_index++;
	return (pinfo->slot_index);
}