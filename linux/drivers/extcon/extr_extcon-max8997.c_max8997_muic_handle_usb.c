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
struct max8997_muic_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  edev; int /*<<< orphan*/  path_usb; } ;
typedef  enum max8997_muic_usb_type { ____Placeholder_max8997_muic_usb_type } max8997_muic_usb_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_SDP ; 
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
#define  MAX8997_USB_DEVICE 129 
#define  MAX8997_USB_HOST 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max8997_muic_set_path (struct max8997_muic_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max8997_muic_handle_usb(struct max8997_muic_info *info,
			enum max8997_muic_usb_type usb_type, bool attached)
{
	int ret = 0;

	ret = max8997_muic_set_path(info, info->path_usb, attached);
	if (ret < 0) {
		dev_err(info->dev, "failed to update muic register\n");
		return ret;
	}

	switch (usb_type) {
	case MAX8997_USB_HOST:
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, attached);
		break;
	case MAX8997_USB_DEVICE:
		extcon_set_state_sync(info->edev, EXTCON_USB, attached);
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);
		break;
	default:
		dev_err(info->dev, "failed to detect %s usb cable\n",
			attached ? "attached" : "detached");
		return -EINVAL;
	}

	return 0;
}