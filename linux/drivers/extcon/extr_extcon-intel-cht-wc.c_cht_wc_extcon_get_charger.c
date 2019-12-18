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
struct cht_wc_extcon_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHT_WC_USBSRC ; 
 int CHT_WC_USBSRC_STS_FAIL ; 
 int CHT_WC_USBSRC_STS_MASK ; 
 int CHT_WC_USBSRC_STS_SUCCESS ; 
#define  CHT_WC_USBSRC_TYPE_ACA 135 
#define  CHT_WC_USBSRC_TYPE_CDP 134 
#define  CHT_WC_USBSRC_TYPE_DCP 133 
#define  CHT_WC_USBSRC_TYPE_DCP_EXTPHY 132 
#define  CHT_WC_USBSRC_TYPE_FLOATING 131 
 int CHT_WC_USBSRC_TYPE_MASK ; 
#define  CHT_WC_USBSRC_TYPE_MHL 130 
#define  CHT_WC_USBSRC_TYPE_OTHER 129 
#define  CHT_WC_USBSRC_TYPE_SDP 128 
 int CHT_WC_USBSRC_TYPE_SHIFT ; 
 int EXTCON_CHG_USB_ACA ; 
 int EXTCON_CHG_USB_CDP ; 
 int EXTCON_CHG_USB_DCP ; 
 int EXTCON_CHG_USB_SDP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int cht_wc_extcon_get_charger(struct cht_wc_extcon_data *ext,
				     bool ignore_errors)
{
	int ret, usbsrc, status;
	unsigned long timeout;

	/* Charger detection can take upto 600ms, wait 800ms max. */
	timeout = jiffies + msecs_to_jiffies(800);
	do {
		ret = regmap_read(ext->regmap, CHT_WC_USBSRC, &usbsrc);
		if (ret) {
			dev_err(ext->dev, "Error reading usbsrc: %d\n", ret);
			return ret;
		}

		status = usbsrc & CHT_WC_USBSRC_STS_MASK;
		if (status == CHT_WC_USBSRC_STS_SUCCESS ||
		    status == CHT_WC_USBSRC_STS_FAIL)
			break;

		msleep(50); /* Wait a bit before retrying */
	} while (time_before(jiffies, timeout));

	if (status != CHT_WC_USBSRC_STS_SUCCESS) {
		if (ignore_errors)
			return EXTCON_CHG_USB_SDP; /* Save fallback */

		if (status == CHT_WC_USBSRC_STS_FAIL)
			dev_warn(ext->dev, "Could not detect charger type\n");
		else
			dev_warn(ext->dev, "Timeout detecting charger type\n");
		return EXTCON_CHG_USB_SDP; /* Save fallback */
	}

	usbsrc = (usbsrc & CHT_WC_USBSRC_TYPE_MASK) >> CHT_WC_USBSRC_TYPE_SHIFT;
	switch (usbsrc) {
	default:
		dev_warn(ext->dev,
			"Unhandled charger type %d, defaulting to SDP\n",
			 ret);
		return EXTCON_CHG_USB_SDP;
	case CHT_WC_USBSRC_TYPE_SDP:
	case CHT_WC_USBSRC_TYPE_FLOATING:
	case CHT_WC_USBSRC_TYPE_OTHER:
		return EXTCON_CHG_USB_SDP;
	case CHT_WC_USBSRC_TYPE_CDP:
		return EXTCON_CHG_USB_CDP;
	case CHT_WC_USBSRC_TYPE_DCP:
	case CHT_WC_USBSRC_TYPE_DCP_EXTPHY:
	case CHT_WC_USBSRC_TYPE_MHL: /* MHL2+ delivers upto 2A, treat as DCP */
		return EXTCON_CHG_USB_DCP;
	case CHT_WC_USBSRC_TYPE_ACA:
		return EXTCON_CHG_USB_ACA;
	}
}