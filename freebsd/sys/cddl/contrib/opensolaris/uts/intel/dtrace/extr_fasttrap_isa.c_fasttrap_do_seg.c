#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct user_segment_descriptor {scalar_t__ sd_dpl; int sd_p; size_t sd_type; scalar_t__ sd_def32; scalar_t__ sd_gran; } ;
struct segment_descriptor {scalar_t__ sd_dpl; int sd_p; size_t sd_type; scalar_t__ sd_def32; scalar_t__ sd_gran; } ;
struct reg {size_t r_cs; size_t r_ds; size_t r_es; size_t r_fs; size_t r_gs; size_t r_ss; } ;
struct TYPE_10__ {TYPE_1__* md_ldt; } ;
struct TYPE_11__ {TYPE_2__ p_md; } ;
typedef  TYPE_3__ proc_t ;
struct TYPE_12__ {int ftt_segment; } ;
typedef  TYPE_4__ fasttrap_tracepoint_t ;
struct TYPE_13__ {struct user_segment_descriptor sd; } ;
struct TYPE_9__ {size_t ldt_len; scalar_t__ ldt_base; } ;

/* Variables and functions */
#define  FASTTRAP_SEG_CS 133 
#define  FASTTRAP_SEG_DS 132 
#define  FASTTRAP_SEG_ES 131 
#define  FASTTRAP_SEG_FS 130 
#define  FASTTRAP_SEG_GS 129 
#define  FASTTRAP_SEG_SS 128 
 size_t IDXSEL (size_t) ; 
 scalar_t__ ISLDT (size_t) ; 
 scalar_t__ ISPL (size_t) ; 
 size_t NGDT ; 
 int PAGESIZE ; 
 struct user_segment_descriptor** PCPU_PTR (TYPE_5__*) ; 
 scalar_t__ SEL_UPL ; 
 scalar_t__ USD_GETBASE (struct user_segment_descriptor*) ; 
 int USD_GETLIMIT (struct user_segment_descriptor*) ; 
 TYPE_3__* curproc ; 
 TYPE_5__* gdt ; 
 size_t max_ldt_segment ; 

__attribute__((used)) static int
fasttrap_do_seg(fasttrap_tracepoint_t *tp, struct reg *rp, uintptr_t *addr)
{
	proc_t *p = curproc;
#ifdef __i386__
	struct segment_descriptor *desc;
#else
	struct user_segment_descriptor *desc;
#endif
	uint16_t sel = 0, ndx, type;
	uintptr_t limit;

	switch (tp->ftt_segment) {
	case FASTTRAP_SEG_CS:
		sel = rp->r_cs;
		break;
	case FASTTRAP_SEG_DS:
		sel = rp->r_ds;
		break;
	case FASTTRAP_SEG_ES:
		sel = rp->r_es;
		break;
	case FASTTRAP_SEG_FS:
		sel = rp->r_fs;
		break;
	case FASTTRAP_SEG_GS:
		sel = rp->r_gs;
		break;
	case FASTTRAP_SEG_SS:
		sel = rp->r_ss;
		break;
	}

	/*
	 * Make sure the given segment register specifies a user priority
	 * selector rather than a kernel selector.
	 */
	if (ISPL(sel) != SEL_UPL)
		return (-1);

	ndx = IDXSEL(sel);

	/*
	 * Check the bounds and grab the descriptor out of the specified
	 * descriptor table.
	 */
	if (ISLDT(sel)) {
#ifdef __i386__
		if (ndx > p->p_md.md_ldt->ldt_len)
			return (-1);

		desc = (struct segment_descriptor *)
		    p->p_md.md_ldt[ndx].ldt_base;
#else
		if (ndx > max_ldt_segment)
			return (-1);

		desc = (struct user_segment_descriptor *)
		    p->p_md.md_ldt[ndx].ldt_base;
#endif

	} else {
		if (ndx >= NGDT)
			return (-1);

#ifdef __i386__
		desc = &gdt[ndx].sd;
#else
		desc = PCPU_PTR(gdt)[ndx];
#endif
	}

	/*
	 * The descriptor must have user privilege level and it must be
	 * present in memory.
	 */
	if (desc->sd_dpl != SEL_UPL || desc->sd_p != 1)
		return (-1);

	type = desc->sd_type;

	/*
	 * If the S bit in the type field is not set, this descriptor can
	 * only be used in system context.
	 */
	if ((type & 0x10) != 0x10)
		return (-1);

	limit = USD_GETLIMIT(desc) * (desc->sd_gran ? PAGESIZE : 1);

	if (tp->ftt_segment == FASTTRAP_SEG_CS) {
		/*
		 * The code/data bit and readable bit must both be set.
		 */
		if ((type & 0xa) != 0xa)
			return (-1);

		if (*addr > limit)
			return (-1);
	} else {
		/*
		 * The code/data bit must be clear.
		 */
		if ((type & 0x8) != 0)
			return (-1);

		/*
		 * If the expand-down bit is clear, we just check the limit as
		 * it would naturally be applied. Otherwise, we need to check
		 * that the address is the range [limit + 1 .. 0xffff] or
		 * [limit + 1 ... 0xffffffff] depending on if the default
		 * operand size bit is set.
		 */
		if ((type & 0x4) == 0) {
			if (*addr > limit)
				return (-1);
		} else if (desc->sd_def32) {
			if (*addr < limit + 1 || 0xffff < *addr)
				return (-1);
		} else {
			if (*addr < limit + 1 || 0xffffffff < *addr)
				return (-1);
		}
	}

	*addr += USD_GETBASE(desc);

	return (0);
}