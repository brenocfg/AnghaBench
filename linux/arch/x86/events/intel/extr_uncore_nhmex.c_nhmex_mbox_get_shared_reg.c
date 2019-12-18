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
typedef  int u64 ;
struct intel_uncore_extra_reg {int config; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; } ;
struct intel_uncore_box {struct intel_uncore_extra_reg* shared_regs; } ;

/* Variables and functions */
 int EXTRA_REG_NHMEX_M_ZDP_CTL_FVC ; 
 int NHMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK (int) ; 
 int NHMEX_M_PMON_ZDP_CTL_FVC_MASK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int WSMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK (int) ; 
 int WSMEX_M_PMON_ZDP_CTL_FVC_MASK ; 
 scalar_t__ __BITS_VALUE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ uncore_nhmex ; 

__attribute__((used)) static bool nhmex_mbox_get_shared_reg(struct intel_uncore_box *box, int idx, u64 config)
{
	struct intel_uncore_extra_reg *er;
	unsigned long flags;
	bool ret = false;
	u64 mask;

	if (idx < EXTRA_REG_NHMEX_M_ZDP_CTL_FVC) {
		er = &box->shared_regs[idx];
		raw_spin_lock_irqsave(&er->lock, flags);
		if (!atomic_read(&er->ref) || er->config == config) {
			atomic_inc(&er->ref);
			er->config = config;
			ret = true;
		}
		raw_spin_unlock_irqrestore(&er->lock, flags);

		return ret;
	}
	/*
	 * The ZDP_CTL_FVC MSR has 4 fields which are used to control
	 * events 0xd ~ 0x10. Besides these 4 fields, there are additional
	 * fields which are shared.
	 */
	idx -= EXTRA_REG_NHMEX_M_ZDP_CTL_FVC;
	if (WARN_ON_ONCE(idx >= 4))
		return false;

	/* mask of the shared fields */
	if (uncore_nhmex)
		mask = NHMEX_M_PMON_ZDP_CTL_FVC_MASK;
	else
		mask = WSMEX_M_PMON_ZDP_CTL_FVC_MASK;
	er = &box->shared_regs[EXTRA_REG_NHMEX_M_ZDP_CTL_FVC];

	raw_spin_lock_irqsave(&er->lock, flags);
	/* add mask of the non-shared field if it's in use */
	if (__BITS_VALUE(atomic_read(&er->ref), idx, 8)) {
		if (uncore_nhmex)
			mask |= NHMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
		else
			mask |= WSMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
	}

	if (!atomic_read(&er->ref) || !((er->config ^ config) & mask)) {
		atomic_add(1 << (idx * 8), &er->ref);
		if (uncore_nhmex)
			mask = NHMEX_M_PMON_ZDP_CTL_FVC_MASK |
				NHMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
		else
			mask = WSMEX_M_PMON_ZDP_CTL_FVC_MASK |
				WSMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
		er->config &= ~mask;
		er->config |= (config & mask);
		ret = true;
	}
	raw_spin_unlock_irqrestore(&er->lock, flags);

	return ret;
}