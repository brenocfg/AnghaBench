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
struct cht_wc_extcon_data {int usb_host; unsigned int previous_cable; int /*<<< orphan*/  edev; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHT_WC_PWRSRC_STS ; 
 int CHT_WC_PWRSRC_VBUS ; 
 unsigned int EXTCON_NONE ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int INTEL_USB_ID_GND ; 
 int INTEL_USB_RID_A ; 
 int /*<<< orphan*/  MUX_SEL_PMIC ; 
 int /*<<< orphan*/  MUX_SEL_SOC ; 
 int /*<<< orphan*/  cht_wc_extcon_enable_charging (struct cht_wc_extcon_data*,int) ; 
 int cht_wc_extcon_get_charger (struct cht_wc_extcon_data*,int) ; 
 int cht_wc_extcon_get_id (struct cht_wc_extcon_data*,int) ; 
 int /*<<< orphan*/  cht_wc_extcon_set_otgmode (struct cht_wc_extcon_data*,int) ; 
 int /*<<< orphan*/  cht_wc_extcon_set_phymux (struct cht_wc_extcon_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cht_wc_extcon_set_state (struct cht_wc_extcon_data*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void cht_wc_extcon_pwrsrc_event(struct cht_wc_extcon_data *ext)
{
	int ret, pwrsrc_sts, id;
	unsigned int cable = EXTCON_NONE;
	/* Ignore errors in host mode, as the 5v boost converter is on then */
	bool ignore_get_charger_errors = ext->usb_host;

	ret = regmap_read(ext->regmap, CHT_WC_PWRSRC_STS, &pwrsrc_sts);
	if (ret) {
		dev_err(ext->dev, "Error reading pwrsrc status: %d\n", ret);
		return;
	}

	id = cht_wc_extcon_get_id(ext, pwrsrc_sts);
	if (id == INTEL_USB_ID_GND) {
		cht_wc_extcon_enable_charging(ext, false);
		cht_wc_extcon_set_otgmode(ext, true);

		/* The 5v boost causes a false VBUS / SDP detect, skip */
		goto charger_det_done;
	}

	cht_wc_extcon_set_otgmode(ext, false);
	cht_wc_extcon_enable_charging(ext, true);

	/* Plugged into a host/charger or not connected? */
	if (!(pwrsrc_sts & CHT_WC_PWRSRC_VBUS)) {
		/* Route D+ and D- to PMIC for future charger detection */
		cht_wc_extcon_set_phymux(ext, MUX_SEL_PMIC);
		goto set_state;
	}

	ret = cht_wc_extcon_get_charger(ext, ignore_get_charger_errors);
	if (ret >= 0)
		cable = ret;

charger_det_done:
	/* Route D+ and D- to SoC for the host or gadget controller */
	cht_wc_extcon_set_phymux(ext, MUX_SEL_SOC);

set_state:
	if (cable != ext->previous_cable) {
		cht_wc_extcon_set_state(ext, cable, true);
		cht_wc_extcon_set_state(ext, ext->previous_cable, false);
		ext->previous_cable = cable;
	}

	ext->usb_host = ((id == INTEL_USB_ID_GND) || (id == INTEL_USB_RID_A));
	extcon_set_state_sync(ext->edev, EXTCON_USB_HOST, ext->usb_host);
}