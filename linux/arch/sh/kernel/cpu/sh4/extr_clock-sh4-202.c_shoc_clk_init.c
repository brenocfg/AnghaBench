#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clk {TYPE_2__* parent; TYPE_1__* ops; } ;
struct TYPE_4__ {int rate; } ;
struct TYPE_3__ {scalar_t__ (* set_rate ) (struct clk*,int) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int* frqcr3_divisors ; 
 scalar_t__ stub1 (struct clk*,int) ; 

__attribute__((used)) static void shoc_clk_init(struct clk *clk)
{
	int i;

	/*
	 * For some reason, the shoc_clk seems to be set to some really
	 * insane value at boot (values outside of the allowable frequency
	 * range for instance). We deal with this by scaling it back down
	 * to something sensible just in case.
	 *
	 * Start scaling from the high end down until we find something
	 * that passes rate verification..
	 */
	for (i = 0; i < ARRAY_SIZE(frqcr3_divisors); i++) {
		int divisor = frqcr3_divisors[i];

		if (clk->ops->set_rate(clk, clk->parent->rate / divisor) == 0)
			break;
	}

	WARN_ON(i == ARRAY_SIZE(frqcr3_divisors));	/* Undefined clock */
}