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
typedef  size_t u16 ;
struct TYPE_4__ {int /*<<< orphan*/  invalidate_other; TYPE_1__* ctxs; int /*<<< orphan*/  loaded_mm_asid; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctx_id; } ;

/* Variables and functions */
 size_t TLB_NR_DYN_ASIDS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  X86_FEATURE_PTI ; 
 TYPE_2__ cpu_tlbstate ; 
 int /*<<< orphan*/  static_cpu_has (int /*<<< orphan*/ ) ; 
 size_t this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_asid_other(void)
{
	u16 asid;

	/*
	 * This is only expected to be set if we have disabled
	 * kernel _PAGE_GLOBAL pages.
	 */
	if (!static_cpu_has(X86_FEATURE_PTI)) {
		WARN_ON_ONCE(1);
		return;
	}

	for (asid = 0; asid < TLB_NR_DYN_ASIDS; asid++) {
		/* Do not need to flush the current asid */
		if (asid == this_cpu_read(cpu_tlbstate.loaded_mm_asid))
			continue;
		/*
		 * Make sure the next time we go to switch to
		 * this asid, we do a flush:
		 */
		this_cpu_write(cpu_tlbstate.ctxs[asid].ctx_id, 0);
	}
	this_cpu_write(cpu_tlbstate.invalidate_other, false);
}