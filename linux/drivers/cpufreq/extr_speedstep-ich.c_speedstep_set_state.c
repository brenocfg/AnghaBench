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
typedef  int u8 ;

/* Variables and functions */
 int inb (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int pmbase ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int speedstep_get_frequency (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speedstep_processor ; 

__attribute__((used)) static void speedstep_set_state(unsigned int state)
{
	u8 pm2_blk;
	u8 value;
	unsigned long flags;

	if (state > 0x1)
		return;

	/* Disable IRQs */
	local_irq_save(flags);

	/* read state */
	value = inb(pmbase + 0x50);

	pr_debug("read at pmbase 0x%x + 0x50 returned 0x%x\n", pmbase, value);

	/* write new state */
	value &= 0xFE;
	value |= state;

	pr_debug("writing 0x%x to pmbase 0x%x + 0x50\n", value, pmbase);

	/* Disable bus master arbitration */
	pm2_blk = inb(pmbase + 0x20);
	pm2_blk |= 0x01;
	outb(pm2_blk, (pmbase + 0x20));

	/* Actual transition */
	outb(value, (pmbase + 0x50));

	/* Restore bus master arbitration */
	pm2_blk &= 0xfe;
	outb(pm2_blk, (pmbase + 0x20));

	/* check if transition was successful */
	value = inb(pmbase + 0x50);

	/* Enable IRQs */
	local_irq_restore(flags);

	pr_debug("read at pmbase 0x%x + 0x50 returned 0x%x\n", pmbase, value);

	if (state == (value & 0x1))
		pr_debug("change to %u MHz succeeded\n",
			speedstep_get_frequency(speedstep_processor) / 1000);
	else
		pr_err("change failed - I/O error\n");

	return;
}