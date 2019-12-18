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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ MMC_POLL_RATE ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mmc_detect_int (int,void*) ; 
 int /*<<< orphan*/  mmc_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static irqreturn_t lubbock_detect_int(int irq, void *data)
{
	/* IRQ is level triggered; disable, and poll for removal */
	disable_irq(irq);
	mod_timer(&mmc_timer, jiffies + MMC_POLL_RATE);

	return mmc_detect_int(irq, data);
}