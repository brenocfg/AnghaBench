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
 int MAS4_MD ; 
 int MAS4_TLBSELD0 ; 
 int MAS4_TSIZED_MASK ; 
 int MAS4_TSIZED_SHIFT ; 
 int /*<<< orphan*/  SPR_MAS4 ; 
 int TLB_SIZE_4K ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_mas4_defaults(void)
{
	uint32_t mas4;

	/* Defaults: TLB0, PID0, TSIZED=4K */
	mas4 = MAS4_TLBSELD0;
	mas4 |= (TLB_SIZE_4K << MAS4_TSIZED_SHIFT) & MAS4_TSIZED_MASK;
#ifdef SMP
	mas4 |= MAS4_MD;
#endif
	mtspr(SPR_MAS4, mas4);
	__asm __volatile("isync");
}