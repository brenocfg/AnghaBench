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
struct mce_bank {int /*<<< orphan*/  ctl; } ;
struct mce {int bank; int status; int severity; scalar_t__ addr; scalar_t__ misc; } ;
struct mca_config {int /*<<< orphan*/  tolerant; scalar_t__ ser; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* status ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int MCE_KEEP_SEVERITY ; 
 int MCE_NO_SEVERITY ; 
 int MCE_UCNA_SEVERITY ; 
 int MCI_STATUS_S ; 
 int MCI_STATUS_UC ; 
 int MCI_STATUS_VAL ; 
 int /*<<< orphan*/  TAINT_MACHINE_CHECK ; 
 int /*<<< orphan*/  __clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mca_config mca_cfg ; 
 int /*<<< orphan*/  mce_banks_array ; 
 int /*<<< orphan*/  mce_log (struct mce*) ; 
 int /*<<< orphan*/  mce_num_banks ; 
 int mce_rdmsrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_read_aux (struct mce*,int) ; 
 int mce_severity (struct mce*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ msr_ops ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 
 struct mce_bank* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mc_scan_banks(struct mce *m, struct mce *final,
			    unsigned long *toclear, unsigned long *valid_banks,
			    int no_way_out, int *worst)
{
	struct mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	struct mca_config *cfg = &mca_cfg;
	int severity, i;

	for (i = 0; i < this_cpu_read(mce_num_banks); i++) {
		__clear_bit(i, toclear);
		if (!test_bit(i, valid_banks))
			continue;

		if (!mce_banks[i].ctl)
			continue;

		m->misc = 0;
		m->addr = 0;
		m->bank = i;

		m->status = mce_rdmsrl(msr_ops.status(i));
		if (!(m->status & MCI_STATUS_VAL))
			continue;

		/*
		 * Corrected or non-signaled errors are handled by
		 * machine_check_poll(). Leave them alone, unless this panics.
		 */
		if (!(m->status & (cfg->ser ? MCI_STATUS_S : MCI_STATUS_UC)) &&
			!no_way_out)
			continue;

		/* Set taint even when machine check was not enabled. */
		add_taint(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);

		severity = mce_severity(m, cfg->tolerant, NULL, true);

		/*
		 * When machine check was for corrected/deferred handler don't
		 * touch, unless we're panicking.
		 */
		if ((severity == MCE_KEEP_SEVERITY ||
		     severity == MCE_UCNA_SEVERITY) && !no_way_out)
			continue;

		__set_bit(i, toclear);

		/* Machine check event was not enabled. Clear, but ignore. */
		if (severity == MCE_NO_SEVERITY)
			continue;

		mce_read_aux(m, i);

		/* assuming valid severity level != 0 */
		m->severity = severity;

		mce_log(m);

		if (severity > *worst) {
			*final = *m;
			*worst = severity;
		}
	}

	/* mce_clear_state will clear *final, save locally for use later */
	*m = *final;
}