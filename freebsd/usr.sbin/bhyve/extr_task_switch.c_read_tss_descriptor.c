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
typedef  int /*<<< orphan*/  uint16_t ;
struct vmctx {int dummy; } ;
struct vm_guest_paging {scalar_t__ cpl; } ;
struct vm_task_switch {scalar_t__ reason; struct vm_guest_paging paging; int /*<<< orphan*/  ext; } ;
struct user_segment_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDT_GP ; 
 int /*<<< orphan*/  IDT_TS ; 
 scalar_t__ IDXSEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISLDT (int /*<<< orphan*/ ) ; 
 scalar_t__ TSR_IRET ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ desc_table_limit_check (struct vmctx*,int,int /*<<< orphan*/ ) ; 
 int desc_table_read (struct vmctx*,int,struct vm_guest_paging*,int /*<<< orphan*/ ,struct user_segment_descriptor*,int*) ; 
 int /*<<< orphan*/  sel_exception (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_tss_descriptor(struct vmctx *ctx, int vcpu, struct vm_task_switch *ts,
    uint16_t sel, struct user_segment_descriptor *desc, int *faultptr)
{
	struct vm_guest_paging sup_paging;
	int error;

	assert(!ISLDT(sel));
	assert(IDXSEL(sel) != 0);

	/* Fetch the new TSS descriptor */
	if (desc_table_limit_check(ctx, vcpu, sel)) {
		if (ts->reason == TSR_IRET)
			sel_exception(ctx, vcpu, IDT_TS, sel, ts->ext);
		else
			sel_exception(ctx, vcpu, IDT_GP, sel, ts->ext);
		return (1);
	}

	sup_paging = ts->paging;
	sup_paging.cpl = 0;		/* implicit supervisor mode */
	error = desc_table_read(ctx, vcpu, &sup_paging, sel, desc, faultptr);
	return (error);
}