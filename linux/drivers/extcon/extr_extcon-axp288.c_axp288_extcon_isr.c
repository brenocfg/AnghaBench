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
struct axp288_extcon_info {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int axp288_handle_chrg_det_event (struct axp288_extcon_info*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static irqreturn_t axp288_extcon_isr(int irq, void *data)
{
	struct axp288_extcon_info *info = data;
	int ret;

	ret = axp288_handle_chrg_det_event(info);
	if (ret < 0)
		dev_err(info->dev, "failed to handle the interrupt\n");

	return IRQ_HANDLED;
}