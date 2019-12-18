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
 int /*<<< orphan*/  __do_cyrix_devid (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void do_cyrix_devid(unsigned char *dir0, unsigned char *dir1)
{
	unsigned long flags;

	local_irq_save(flags);
	__do_cyrix_devid(dir0, dir1);
	local_irq_restore(flags);
}