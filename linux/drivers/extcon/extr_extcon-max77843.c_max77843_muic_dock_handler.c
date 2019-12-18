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
struct max77843_muic_info {int /*<<< orphan*/  edev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_DISP_MHL ; 
 int /*<<< orphan*/  EXTCON_DOCK ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  MAX77843_MUIC_CONTROL1_SW_USB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max77843_muic_set_path (struct max77843_muic_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max77843_muic_dock_handler(struct max77843_muic_info *info,
		bool attached)
{
	int ret;

	dev_dbg(info->dev, "external connector is %s (adc: 0x10)\n",
			attached ? "attached" : "detached");

	ret = max77843_muic_set_path(info, MAX77843_MUIC_CONTROL1_SW_USB,
				     attached, attached);
	if (ret < 0)
		return ret;

	extcon_set_state_sync(info->edev, EXTCON_DISP_MHL, attached);
	extcon_set_state_sync(info->edev, EXTCON_USB_HOST, attached);
	extcon_set_state_sync(info->edev, EXTCON_DOCK, attached);

	return 0;
}