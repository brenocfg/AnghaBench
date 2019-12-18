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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tlb_invalid_all () ; 

void flush_tlb_mm(struct mm_struct *mm)
{
#ifdef CONFIG_CPU_HAS_TLBI
	asm volatile("tlbi.asids %0"::"r"(cpu_asid(mm)));
#else
	tlb_invalid_all();
#endif
}