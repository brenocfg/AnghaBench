#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * cb; } ;

/* Variables and functions */
 int BCM63XX_TIMER_COUNT ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* timer_data ; 
 int /*<<< orphan*/  timer_data_lock ; 

void bcm63xx_timer_unregister(int id)
{
	unsigned long flags;

	if (id >= BCM63XX_TIMER_COUNT)
		return;

	raw_spin_lock_irqsave(&timer_data_lock, flags);
	timer_data[id].cb = NULL;
	raw_spin_unlock_irqrestore(&timer_data_lock, flags);
}