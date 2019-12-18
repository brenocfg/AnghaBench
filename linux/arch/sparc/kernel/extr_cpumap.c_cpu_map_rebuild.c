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
 int /*<<< orphan*/  _cpu_map_rebuild () ; 
 int /*<<< orphan*/  cpu_map_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cpu_map_rebuild(void)
{
	unsigned long flag;

	spin_lock_irqsave(&cpu_map_lock, flag);
	_cpu_map_rebuild();
	spin_unlock_irqrestore(&cpu_map_lock, flag);
}