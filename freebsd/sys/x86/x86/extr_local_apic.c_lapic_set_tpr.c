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
typedef  int u_int ;

/* Variables and functions */
 int APIC_TPR_PRIO ; 
 int /*<<< orphan*/  LAPIC_TPR ; 
 int lapic_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_write32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lapic_set_tpr(u_int vector)
{
#ifdef CHEAP_TPR
	lapic_write32(LAPIC_TPR, vector);
#else
	uint32_t tpr;

	tpr = lapic_read32(LAPIC_TPR) & ~APIC_TPR_PRIO;
	tpr |= vector;
	lapic_write32(LAPIC_TPR, tpr);
#endif
}