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
 int fdc_busy ; 
 int /*<<< orphan*/  fdc_nested ; 
 int /*<<< orphan*/  fdc_wait ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_fdc (int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_fdc(int drive)
{
	unsigned long flags;

	drive &= 3;
#ifdef DEBUG
	printk("get_fdc: drive %d  fdc_busy %d  fdc_nested %d\n",drive,fdc_busy,fdc_nested);
#endif
	local_irq_save(flags);
	wait_event(fdc_wait, try_fdc(drive));
	fdc_busy = drive;
	fdc_nested++;
	local_irq_restore(flags);
}