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
struct thread_info {int slb_preload_tail; int slb_preload_nr; unsigned long* slb_preload_esid; } ;

/* Variables and functions */
 unsigned long ESID_MASK_1T ; 
 int /*<<< orphan*/  MMU_FTR_1T_SEGMENT ; 
 unsigned long SID_SHIFT ; 
 int SLB_PRELOAD_NR ; 
 scalar_t__ mmu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ preload_hit (struct thread_info*,unsigned long) ; 

__attribute__((used)) static bool preload_add(struct thread_info *ti, unsigned long ea)
{
	unsigned char idx;
	unsigned long esid;

	if (mmu_has_feature(MMU_FTR_1T_SEGMENT)) {
		/* EAs are stored >> 28 so 256MB segments don't need clearing */
		if (ea & ESID_MASK_1T)
			ea &= ESID_MASK_1T;
	}

	esid = ea >> SID_SHIFT;

	if (preload_hit(ti, esid))
		return false;

	idx = (ti->slb_preload_tail + ti->slb_preload_nr) % SLB_PRELOAD_NR;
	ti->slb_preload_esid[idx] = esid;
	if (ti->slb_preload_nr == SLB_PRELOAD_NR)
		ti->slb_preload_tail = (ti->slb_preload_tail + 1) % SLB_PRELOAD_NR;
	else
		ti->slb_preload_nr++;

	return true;
}