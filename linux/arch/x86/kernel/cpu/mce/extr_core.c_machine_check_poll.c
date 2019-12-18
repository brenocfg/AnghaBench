#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mce_bank {int /*<<< orphan*/  ctl; } ;
struct mce {int bank; int status; int /*<<< orphan*/  severity; scalar_t__ addr; scalar_t__ misc; int /*<<< orphan*/  tsc; } ;
typedef  int /*<<< orphan*/  mce_banks_t ;
typedef  enum mcp_flags { ____Placeholder_mcp_flags } mcp_flags ;
struct TYPE_4__ {int /*<<< orphan*/  dont_log_ce; int /*<<< orphan*/  tolerant; int /*<<< orphan*/  ser; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* status ) (int) ;} ;

/* Variables and functions */
 int MCI_STATUS_EN ; 
 int MCI_STATUS_PCC ; 
 int MCI_STATUS_S ; 
 int MCI_STATUS_UC ; 
 int MCI_STATUS_VAL ; 
 int MCP_DONTLOG ; 
 int MCP_TIMESTAMP ; 
 int MCP_UC ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_2__ mca_cfg ; 
 int /*<<< orphan*/  mce_banks_array ; 
 int /*<<< orphan*/  mce_gather_info (struct mce*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_gen_pool_add (struct mce*) ; 
 int /*<<< orphan*/  mce_log (struct mce*) ; 
 int /*<<< orphan*/  mce_num_banks ; 
 int /*<<< orphan*/  mce_poll_count ; 
 int mce_rdmsrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_read_aux (struct mce*,int) ; 
 int /*<<< orphan*/  mce_schedule_work () ; 
 int /*<<< orphan*/  mce_severity (struct mce*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mce_usable_address (struct mce*) ; 
 int /*<<< orphan*/  mce_wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ msr_ops ; 
 int /*<<< orphan*/  rdtsc () ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  sync_core () ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct mce_bank* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 

bool machine_check_poll(enum mcp_flags flags, mce_banks_t *b)
{
	struct mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	bool error_seen = false;
	struct mce m;
	int i;

	this_cpu_inc(mce_poll_count);

	mce_gather_info(&m, NULL);

	if (flags & MCP_TIMESTAMP)
		m.tsc = rdtsc();

	for (i = 0; i < this_cpu_read(mce_num_banks); i++) {
		if (!mce_banks[i].ctl || !test_bit(i, *b))
			continue;

		m.misc = 0;
		m.addr = 0;
		m.bank = i;

		barrier();
		m.status = mce_rdmsrl(msr_ops.status(i));

		/* If this entry is not valid, ignore it */
		if (!(m.status & MCI_STATUS_VAL))
			continue;

		/*
		 * If we are logging everything (at CPU online) or this
		 * is a corrected error, then we must log it.
		 */
		if ((flags & MCP_UC) || !(m.status & MCI_STATUS_UC))
			goto log_it;

		/*
		 * Newer Intel systems that support software error
		 * recovery need to make additional checks. Other
		 * CPUs should skip over uncorrected errors, but log
		 * everything else.
		 */
		if (!mca_cfg.ser) {
			if (m.status & MCI_STATUS_UC)
				continue;
			goto log_it;
		}

		/* Log "not enabled" (speculative) errors */
		if (!(m.status & MCI_STATUS_EN))
			goto log_it;

		/*
		 * Log UCNA (SDM: 15.6.3 "UCR Error Classification")
		 * UC == 1 && PCC == 0 && S == 0
		 */
		if (!(m.status & MCI_STATUS_PCC) && !(m.status & MCI_STATUS_S))
			goto log_it;

		/*
		 * Skip anything else. Presumption is that our read of this
		 * bank is racing with a machine check. Leave the log alone
		 * for do_machine_check() to deal with it.
		 */
		continue;

log_it:
		error_seen = true;

		mce_read_aux(&m, i);

		m.severity = mce_severity(&m, mca_cfg.tolerant, NULL, false);

		/*
		 * Don't get the IP here because it's unlikely to
		 * have anything to do with the actual error location.
		 */
		if (!(flags & MCP_DONTLOG) && !mca_cfg.dont_log_ce)
			mce_log(&m);
		else if (mce_usable_address(&m)) {
			/*
			 * Although we skipped logging this, we still want
			 * to take action. Add to the pool so the registered
			 * notifiers will see it.
			 */
			if (!mce_gen_pool_add(&m))
				mce_schedule_work();
		}

		/*
		 * Clear state for this bank.
		 */
		mce_wrmsrl(msr_ops.status(i), 0);
	}

	/*
	 * Don't clear MCG_STATUS here because it's only defined for
	 * exceptions.
	 */

	sync_core();

	return error_seen;
}