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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_FAN ; 
 int /*<<< orphan*/  nw_gpio_lock ; 
 int /*<<< orphan*/  nw_gpio_modify_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void netwinder_set_fan(int i)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&nw_gpio_lock, flags);
	nw_gpio_modify_op(GPIO_FAN, i ? GPIO_FAN : 0);
	raw_spin_unlock_irqrestore(&nw_gpio_lock, flags);
}