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
typedef  unsigned long long u64 ;
struct pt_regs {int dummy; } ;
struct op_msrs {TYPE_1__* counters; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVTPC ; 
 int APIC_LVT_MASKED ; 
 int apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,int) ; 
 int counter_width ; 
 int num_counters ; 
 int /*<<< orphan*/  oprofile_add_sample (struct pt_regs* const,int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/ * reset_value ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppro_check_ctrs(struct pt_regs * const regs,
			   struct op_msrs const * const msrs)
{
	u64 val;
	int i;

	for (i = 0; i < num_counters; ++i) {
		if (!reset_value[i])
			continue;
		rdmsrl(msrs->counters[i].addr, val);
		if (val & (1ULL << (counter_width - 1)))
			continue;
		oprofile_add_sample(regs, i);
		wrmsrl(msrs->counters[i].addr, -reset_value[i]);
	}

	/* Only P6 based Pentium M need to re-unmask the apic vector but it
	 * doesn't hurt other P6 variant */
	apic_write(APIC_LVTPC, apic_read(APIC_LVTPC) & ~APIC_LVT_MASKED);

	/* We can't work out if we really handled an interrupt. We
	 * might have caught a *second* counter just after overflowing
	 * the interrupt for this counter then arrives
	 * and we don't find a counter that's overflowed, so we
	 * would return 0 and get dazed + confused. Instead we always
	 * assume we found an overflow. This sucks.
	 */
	return 1;
}