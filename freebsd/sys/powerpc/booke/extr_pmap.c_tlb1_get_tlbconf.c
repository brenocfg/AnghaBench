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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPR_TLB1CFG ; 
 int TLBCFG_NENTRY_MASK ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int tlb1_entries ; 

__attribute__((used)) static __inline void
tlb1_get_tlbconf(void)
{
	uint32_t tlb1_cfg;

	tlb1_cfg = mfspr(SPR_TLB1CFG);
	tlb1_entries = tlb1_cfg & TLBCFG_NENTRY_MASK;
}