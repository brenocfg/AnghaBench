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
struct cht_wc_extcon_data {int dummy; } ;

/* Variables and functions */
#define  CHT_WC_PWRSRC_RID_ACA 130 
#define  CHT_WC_PWRSRC_RID_FLOAT 129 
#define  CHT_WC_PWRSRC_RID_GND 128 
 int CHT_WC_PWRSRC_USBID_MASK ; 
 int CHT_WC_PWRSRC_USBID_SHIFT ; 
 int INTEL_USB_ID_FLOAT ; 
 int INTEL_USB_ID_GND ; 

__attribute__((used)) static int cht_wc_extcon_get_id(struct cht_wc_extcon_data *ext, int pwrsrc_sts)
{
	switch ((pwrsrc_sts & CHT_WC_PWRSRC_USBID_MASK) >> CHT_WC_PWRSRC_USBID_SHIFT) {
	case CHT_WC_PWRSRC_RID_GND:
		return INTEL_USB_ID_GND;
	case CHT_WC_PWRSRC_RID_FLOAT:
		return INTEL_USB_ID_FLOAT;
	case CHT_WC_PWRSRC_RID_ACA:
	default:
		/*
		 * Once we have IIO support for the GPADC we should read
		 * the USBID GPADC channel here and determine ACA role
		 * based on that.
		 */
		return INTEL_USB_ID_FLOAT;
	}
}