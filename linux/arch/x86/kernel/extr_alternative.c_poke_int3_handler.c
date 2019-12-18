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
struct text_poke_loc {void* addr; scalar_t__ detour; } ;
struct pt_regs {unsigned long ip; } ;
typedef  int /*<<< orphan*/  int3 ;
struct TYPE_2__ {int nr_entries; struct text_poke_loc* vec; } ;

/* Variables and functions */
 TYPE_1__ bp_patching ; 
 struct text_poke_loc* bsearch (void*,struct text_poke_loc*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  patch_cmp ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

int poke_int3_handler(struct pt_regs *regs)
{
	struct text_poke_loc *tp;
	unsigned char int3 = 0xcc;
	void *ip;

	/*
	 * Having observed our INT3 instruction, we now must observe
	 * bp_patching.nr_entries.
	 *
	 * 	nr_entries != 0			INT3
	 * 	WMB				RMB
	 * 	write INT3			if (nr_entries)
	 *
	 * Idem for other elements in bp_patching.
	 */
	smp_rmb();

	if (likely(!bp_patching.nr_entries))
		return 0;

	if (user_mode(regs))
		return 0;

	/*
	 * Discount the sizeof(int3). See text_poke_bp_batch().
	 */
	ip = (void *) regs->ip - sizeof(int3);

	/*
	 * Skip the binary search if there is a single member in the vector.
	 */
	if (unlikely(bp_patching.nr_entries > 1)) {
		tp = bsearch(ip, bp_patching.vec, bp_patching.nr_entries,
			     sizeof(struct text_poke_loc),
			     patch_cmp);
		if (!tp)
			return 0;
	} else {
		tp = bp_patching.vec;
		if (tp->addr != ip)
			return 0;
	}

	/* set up the specified breakpoint detour */
	regs->ip = (unsigned long) tp->detour;

	return 1;
}