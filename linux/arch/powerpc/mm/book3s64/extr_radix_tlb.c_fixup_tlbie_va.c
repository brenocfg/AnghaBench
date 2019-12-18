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

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_P9_TLBIE_ERAT_BUG ; 
 int /*<<< orphan*/  CPU_FTR_P9_TLBIE_STQ_BUG ; 
 int /*<<< orphan*/  RIC_FLUSH_TLB ; 
 int /*<<< orphan*/  __tlbie_va (unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fixup_tlbie_va(unsigned long va, unsigned long pid,
				  unsigned long ap)
{
	if (cpu_has_feature(CPU_FTR_P9_TLBIE_ERAT_BUG)) {
		asm volatile("ptesync": : :"memory");
		__tlbie_va(va, 0, ap, RIC_FLUSH_TLB);
	}

	if (cpu_has_feature(CPU_FTR_P9_TLBIE_STQ_BUG)) {
		asm volatile("ptesync": : :"memory");
		__tlbie_va(va, pid, ap, RIC_FLUSH_TLB);
	}
}