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
typedef  int uint16_t ;
struct vmctx {int dummy; } ;
struct vm_guest_paging {int /*<<< orphan*/  cpl; } ;
struct vm_task_switch {int /*<<< orphan*/  ext; struct vm_guest_paging paging; } ;
struct user_segment_descriptor {int sd_type; int sd_dpl; int /*<<< orphan*/  sd_p; } ;
struct seg_desc {int access; scalar_t__ limit; scalar_t__ base; } ;

/* Variables and functions */
 int GETREG (struct vmctx*,int,int const) ; 
 int IDT_NP ; 
 int IDT_SS ; 
 int IDT_TS ; 
 scalar_t__ IDXSEL (int) ; 
 scalar_t__ ISLDT (int) ; 
 int SEL_RPL_MASK ; 
#define  VM_REG_GUEST_CS 134 
#define  VM_REG_GUEST_DS 133 
#define  VM_REG_GUEST_ES 132 
#define  VM_REG_GUEST_FS 131 
#define  VM_REG_GUEST_GS 130 
#define  VM_REG_GUEST_LDTR 129 
#define  VM_REG_GUEST_SS 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ code_desc (int) ; 
 int /*<<< orphan*/  data_desc (int) ; 
 scalar_t__ desc_table_limit_check (struct vmctx*,int,int) ; 
 int desc_table_read (struct vmctx*,int,struct vm_guest_paging*,int,struct user_segment_descriptor*,int*) ; 
 int /*<<< orphan*/  ldt_desc (int) ; 
 int /*<<< orphan*/  sel_exception (struct vmctx*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_desc (int) ; 
 struct seg_desc usd_to_seg_desc (struct user_segment_descriptor*) ; 

__attribute__((used)) static int
validate_seg_desc(struct vmctx *ctx, int vcpu, struct vm_task_switch *ts,
    int segment, struct seg_desc *seg_desc, int *faultptr)
{
	struct vm_guest_paging sup_paging;
	struct user_segment_descriptor usd;
	int error, idtvec;
	int cpl, dpl, rpl;
	uint16_t sel, cs;
	bool ldtseg, codeseg, stackseg, dataseg, conforming;

	ldtseg = codeseg = stackseg = dataseg = false;
	switch (segment) {
	case VM_REG_GUEST_LDTR:
		ldtseg = true;
		break;
	case VM_REG_GUEST_CS:
		codeseg = true;
		break;
	case VM_REG_GUEST_SS:
		stackseg = true;
		break;
	case VM_REG_GUEST_DS:
	case VM_REG_GUEST_ES:
	case VM_REG_GUEST_FS:
	case VM_REG_GUEST_GS:
		dataseg = true;
		break;
	default:
		assert(0);
	}

	/* Get the segment selector */
	sel = GETREG(ctx, vcpu, segment);

	/* LDT selector must point into the GDT */
	if (ldtseg && ISLDT(sel)) {
		sel_exception(ctx, vcpu, IDT_TS, sel, ts->ext);
		return (1);
	}

	/* Descriptor table limit check */
	if (desc_table_limit_check(ctx, vcpu, sel)) {
		sel_exception(ctx, vcpu, IDT_TS, sel, ts->ext);
		return (1);
	}

	/* NULL selector */
	if (IDXSEL(sel) == 0) {
		/* Code and stack segment selectors cannot be NULL */
		if (codeseg || stackseg) {
			sel_exception(ctx, vcpu, IDT_TS, sel, ts->ext);
			return (1);
		}
		seg_desc->base = 0;
		seg_desc->limit = 0;
		seg_desc->access = 0x10000;	/* unusable */
		return (0);
	}

	/* Read the descriptor from the GDT/LDT */
	sup_paging = ts->paging;
	sup_paging.cpl = 0;	/* implicit supervisor mode */
	error = desc_table_read(ctx, vcpu, &sup_paging, sel, &usd, faultptr);
	if (error || *faultptr)
		return (error);

	/* Verify that the descriptor type is compatible with the segment */
	if ((ldtseg && !ldt_desc(usd.sd_type)) ||
	    (codeseg && !code_desc(usd.sd_type)) ||
	    (dataseg && !data_desc(usd.sd_type)) ||
	    (stackseg && !stack_desc(usd.sd_type))) {
		sel_exception(ctx, vcpu, IDT_TS, sel, ts->ext);
		return (1);
	}

	/* Segment must be marked present */
	if (!usd.sd_p) {
		if (ldtseg)
			idtvec = IDT_TS;
		else if (stackseg)
			idtvec = IDT_SS;
		else
			idtvec = IDT_NP;
		sel_exception(ctx, vcpu, idtvec, sel, ts->ext);
		return (1);
	}

	cs = GETREG(ctx, vcpu, VM_REG_GUEST_CS);
	cpl = cs & SEL_RPL_MASK;
	rpl = sel & SEL_RPL_MASK;
	dpl = usd.sd_dpl;

	if (stackseg && (rpl != cpl || dpl != cpl)) {
		sel_exception(ctx, vcpu, IDT_TS, sel, ts->ext);
		return (1);
	}

	if (codeseg) {
		conforming = (usd.sd_type & 0x4) ? true : false;
		if ((conforming && (cpl < dpl)) ||
		    (!conforming && (cpl != dpl))) {
			sel_exception(ctx, vcpu, IDT_TS, sel, ts->ext);
			return (1);
		}
	}

	if (dataseg) {
		/*
		 * A data segment is always non-conforming except when it's
		 * descriptor is a readable, conforming code segment.
		 */
		if (code_desc(usd.sd_type) && (usd.sd_type & 0x4) != 0)
			conforming = true;
		else
			conforming = false;

		if (!conforming && (rpl > dpl || cpl > dpl)) {
			sel_exception(ctx, vcpu, IDT_TS, sel, ts->ext);
			return (1);
		}
	}
	*seg_desc = usd_to_seg_desc(&usd);
	return (0);
}