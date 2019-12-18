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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LAPIC_DCR_TIMER ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lapic_timer_divisors ; 
 int /*<<< orphan*/  lapic_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int powerof2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lapic_timer_set_divisor(u_int divisor)
{

	KASSERT(powerof2(divisor), ("lapic: invalid divisor %u", divisor));
	KASSERT(ffs(divisor) <= nitems(lapic_timer_divisors),
		("lapic: invalid divisor %u", divisor));
	lapic_write32(LAPIC_DCR_TIMER, lapic_timer_divisors[ffs(divisor) - 1]);
}