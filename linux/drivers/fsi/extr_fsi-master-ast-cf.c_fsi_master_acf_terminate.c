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
struct fsi_master_acf {scalar_t__ sram; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_ARM_ACK ; 
 scalar_t__ ARB_REG ; 
 scalar_t__ CF_STARTED ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  release_copro_gpios (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  reset_cf (struct fsi_master_acf*) ; 

__attribute__((used)) static void fsi_master_acf_terminate(struct fsi_master_acf *master)
{
	unsigned long flags;

	/*
	 * A GPIO arbitration requestion could come in while this is
	 * happening. To avoid problems, we disable interrupts so it
	 * cannot preempt us on this CPU
	 */

	local_irq_save(flags);

	/* Stop the coprocessor */
	reset_cf(master);

	/* We mark the copro not-started */
	iowrite32(0, master->sram + CF_STARTED);

	/* We mark the ARB register as having given up arbitration to
	 * deal with a potential race with the arbitration request
	 */
	iowrite8(ARB_ARM_ACK, master->sram + ARB_REG);

	local_irq_restore(flags);

	/* Return the GPIOs to the ARM */
	release_copro_gpios(master);
}