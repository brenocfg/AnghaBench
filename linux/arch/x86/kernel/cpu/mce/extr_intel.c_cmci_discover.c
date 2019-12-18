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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ bios_cmci_threshold; } ;

/* Variables and functions */
 int CMCI_THRESHOLD ; 
 int MCI_CTL2_CMCI_EN ; 
 int MCI_CTL2_CMCI_THRESHOLD_MASK ; 
 int /*<<< orphan*/  MSR_IA32_MCx_CTL2 (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  cmci_discover_lock ; 
 TYPE_1__ mca_cfg ; 
 unsigned long* mce_banks_ce_disabled ; 
 int /*<<< orphan*/  mce_banks_owned ; 
 int /*<<< orphan*/ * mce_poll_banks ; 
 int /*<<< orphan*/  pr_info_once (char*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 unsigned long* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cmci_discover(int banks)
{
	unsigned long *owned = (void *)this_cpu_ptr(&mce_banks_owned);
	unsigned long flags;
	int i;
	int bios_wrong_thresh = 0;

	raw_spin_lock_irqsave(&cmci_discover_lock, flags);
	for (i = 0; i < banks; i++) {
		u64 val;
		int bios_zero_thresh = 0;

		if (test_bit(i, owned))
			continue;

		/* Skip banks in firmware first mode */
		if (test_bit(i, mce_banks_ce_disabled))
			continue;

		rdmsrl(MSR_IA32_MCx_CTL2(i), val);

		/* Already owned by someone else? */
		if (val & MCI_CTL2_CMCI_EN) {
			clear_bit(i, owned);
			__clear_bit(i, this_cpu_ptr(mce_poll_banks));
			continue;
		}

		if (!mca_cfg.bios_cmci_threshold) {
			val &= ~MCI_CTL2_CMCI_THRESHOLD_MASK;
			val |= CMCI_THRESHOLD;
		} else if (!(val & MCI_CTL2_CMCI_THRESHOLD_MASK)) {
			/*
			 * If bios_cmci_threshold boot option was specified
			 * but the threshold is zero, we'll try to initialize
			 * it to 1.
			 */
			bios_zero_thresh = 1;
			val |= CMCI_THRESHOLD;
		}

		val |= MCI_CTL2_CMCI_EN;
		wrmsrl(MSR_IA32_MCx_CTL2(i), val);
		rdmsrl(MSR_IA32_MCx_CTL2(i), val);

		/* Did the enable bit stick? -- the bank supports CMCI */
		if (val & MCI_CTL2_CMCI_EN) {
			set_bit(i, owned);
			__clear_bit(i, this_cpu_ptr(mce_poll_banks));
			/*
			 * We are able to set thresholds for some banks that
			 * had a threshold of 0. This means the BIOS has not
			 * set the thresholds properly or does not work with
			 * this boot option. Note down now and report later.
			 */
			if (mca_cfg.bios_cmci_threshold && bios_zero_thresh &&
					(val & MCI_CTL2_CMCI_THRESHOLD_MASK))
				bios_wrong_thresh = 1;
		} else {
			WARN_ON(!test_bit(i, this_cpu_ptr(mce_poll_banks)));
		}
	}
	raw_spin_unlock_irqrestore(&cmci_discover_lock, flags);
	if (mca_cfg.bios_cmci_threshold && bios_wrong_thresh) {
		pr_info_once(
			"bios_cmci_threshold: Some banks do not have valid thresholds set\n");
		pr_info_once(
			"bios_cmci_threshold: Make sure your BIOS supports this boot option\n");
	}
}