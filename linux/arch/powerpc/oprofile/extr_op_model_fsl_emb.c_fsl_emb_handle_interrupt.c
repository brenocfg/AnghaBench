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
struct pt_regs {unsigned long nip; } ;
struct op_counter_config {scalar_t__ enabled; } ;

/* Variables and functions */
 int MSR_PMM ; 
 int ctr_read (int) ; 
 int /*<<< orphan*/  ctr_write (int,int /*<<< orphan*/ ) ; 
 int is_kernel_addr (unsigned long) ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int num_counters ; 
 int /*<<< orphan*/  oprofile_add_ext_sample (unsigned long,struct pt_regs*,int,int) ; 
 scalar_t__ oprofile_running ; 
 int /*<<< orphan*/  pmc_start_ctrs (int) ; 
 int /*<<< orphan*/ * reset_value ; 

__attribute__((used)) static void fsl_emb_handle_interrupt(struct pt_regs *regs,
				    struct op_counter_config *ctr)
{
	unsigned long pc;
	int is_kernel;
	int val;
	int i;

	pc = regs->nip;
	is_kernel = is_kernel_addr(pc);

	for (i = 0; i < num_counters; ++i) {
		val = ctr_read(i);
		if (val < 0) {
			if (oprofile_running && ctr[i].enabled) {
				oprofile_add_ext_sample(pc, regs, i, is_kernel);
				ctr_write(i, reset_value[i]);
			} else {
				ctr_write(i, 0);
			}
		}
	}

	/* The freeze bit was set by the interrupt. */
	/* Clear the freeze bit, and reenable the interrupt.  The
	 * counters won't actually start until the rfi clears the PMM
	 * bit.  The PMM bit should not be set until after the interrupt
	 * is cleared to avoid it getting lost in some hypervisor
	 * environments.
	 */
	mtmsr(mfmsr() | MSR_PMM);
	pmc_start_ctrs(1);
}