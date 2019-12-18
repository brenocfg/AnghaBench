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
typedef  scalar_t__ u32 ;
struct dwapb_gpio {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ dwapb_do_irq (struct dwapb_gpio*) ; 

__attribute__((used)) static irqreturn_t dwapb_irq_handler_mfd(int irq, void *dev_id)
{
	u32 worked;
	struct dwapb_gpio *gpio = dev_id;

	worked = dwapb_do_irq(gpio);

	return worked ? IRQ_HANDLED : IRQ_NONE;
}