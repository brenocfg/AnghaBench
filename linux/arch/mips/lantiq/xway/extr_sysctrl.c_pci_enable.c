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
struct clk {scalar_t__ rate; } ;

/* Variables and functions */
 scalar_t__ CLOCK_33M ; 
 int /*<<< orphan*/  ifccr ; 
 unsigned int ltq_cgu_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_cgu_w32 (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  pmu_enable (struct clk*) ; 

__attribute__((used)) static int pci_enable(struct clk *clk)
{
	unsigned int val = ltq_cgu_r32(ifccr);
	/* set bus clock speed */
	if (of_machine_is_compatible("lantiq,ar9") ||
			of_machine_is_compatible("lantiq,vr9")) {
		val &= ~0x1f00000;
		if (clk->rate == CLOCK_33M)
			val |= 0xe00000;
		else
			val |= 0x700000; /* 62.5M */
	} else {
		val &= ~0xf00000;
		if (clk->rate == CLOCK_33M)
			val |= 0x800000;
		else
			val |= 0x400000; /* 62.5M */
	}
	ltq_cgu_w32(val, ifccr);
	pmu_enable(clk);
	return 0;
}