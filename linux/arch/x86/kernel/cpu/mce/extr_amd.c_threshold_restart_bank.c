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
typedef  int u32 ;
struct thresh_restart {int reset; int old_limit; int lvt_off; TYPE_1__* b; scalar_t__ set_lvt_off; } ;
struct TYPE_2__ {int threshold_limit; int /*<<< orphan*/  address; scalar_t__ interrupt_enable; int /*<<< orphan*/  interrupt_capable; } ;

/* Variables and functions */
 int INT_TYPE_APIC ; 
 int MASK_COUNT_EN_HI ; 
 int MASK_ERR_COUNT_HI ; 
 int MASK_INT_TYPE_HI ; 
 int MASK_LVTOFF_HI ; 
 int MASK_OVERFLOW_HI ; 
 int THRESHOLD_MAX ; 
 scalar_t__ lvt_off_valid (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void threshold_restart_bank(void *_tr)
{
	struct thresh_restart *tr = _tr;
	u32 hi, lo;

	rdmsr(tr->b->address, lo, hi);

	if (tr->b->threshold_limit < (hi & THRESHOLD_MAX))
		tr->reset = 1;	/* limit cannot be lower than err count */

	if (tr->reset) {		/* reset err count and overflow bit */
		hi =
		    (hi & ~(MASK_ERR_COUNT_HI | MASK_OVERFLOW_HI)) |
		    (THRESHOLD_MAX - tr->b->threshold_limit);
	} else if (tr->old_limit) {	/* change limit w/o reset */
		int new_count = (hi & THRESHOLD_MAX) +
		    (tr->old_limit - tr->b->threshold_limit);

		hi = (hi & ~MASK_ERR_COUNT_HI) |
		    (new_count & THRESHOLD_MAX);
	}

	/* clear IntType */
	hi &= ~MASK_INT_TYPE_HI;

	if (!tr->b->interrupt_capable)
		goto done;

	if (tr->set_lvt_off) {
		if (lvt_off_valid(tr->b, tr->lvt_off, lo, hi)) {
			/* set new lvt offset */
			hi &= ~MASK_LVTOFF_HI;
			hi |= tr->lvt_off << 20;
		}
	}

	if (tr->b->interrupt_enable)
		hi |= INT_TYPE_APIC;

 done:

	hi |= MASK_COUNT_EN_HI;
	wrmsr(tr->b->address, lo, hi);
}