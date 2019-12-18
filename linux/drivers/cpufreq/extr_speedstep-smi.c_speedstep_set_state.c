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
struct TYPE_2__ {int frequency; } ;

/* Variables and functions */
 unsigned int SET_SPEEDSTEP_STATE ; 
 unsigned int SMI_TRIES ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mdelay (unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned int,...) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int smi_cmd ; 
 unsigned int smi_port ; 
 int smi_sig ; 
 TYPE_1__* speedstep_freqs ; 

__attribute__((used)) static void speedstep_set_state(unsigned int state)
{
	unsigned int result = 0, command, new_state, dummy;
	unsigned long flags;
	unsigned int function = SET_SPEEDSTEP_STATE;
	unsigned int retry = 0;

	if (state > 0x1)
		return;

	/* Disable IRQs */
	preempt_disable();
	local_irq_save(flags);

	command = (smi_sig & 0xffffff00) | (smi_cmd & 0xff);

	pr_debug("trying to set frequency to state %u "
		"with command %x at port %x\n",
		state, command, smi_port);

	do {
		if (retry) {
			/*
			 * We need to enable interrupts, otherwise the blockage
			 * won't resolve.
			 *
			 * We disable preemption so that other processes don't
			 * run. If other processes were running, they could
			 * submit more DMA requests, making the blockage worse.
			 */
			pr_debug("retry %u, previous result %u, waiting...\n",
					retry, result);
			local_irq_enable();
			mdelay(retry * 50);
			local_irq_disable();
		}
		retry++;
		__asm__ __volatile__(
			"push %%ebp\n"
			"out %%al, (%%dx)\n"
			"pop %%ebp"
			: "=b" (new_state), "=D" (result),
			  "=c" (dummy), "=a" (dummy),
			  "=d" (dummy), "=S" (dummy)
			: "a" (command), "b" (function), "c" (state),
			  "d" (smi_port), "S" (0), "D" (0)
			);
	} while ((new_state != state) && (retry <= SMI_TRIES));

	/* enable IRQs */
	local_irq_restore(flags);
	preempt_enable();

	if (new_state == state)
		pr_debug("change to %u MHz succeeded after %u tries "
			"with result %u\n",
			(speedstep_freqs[new_state].frequency / 1000),
			retry, result);
	else
		pr_err("change to state %u failed with new_state %u and result %u\n",
		       state, new_state, result);

	return;
}