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
struct clk {TYPE_1__* parent; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int* frqcr3_divisors ; 
 int* frqcr3_values ; 

__attribute__((used)) static inline int frqcr3_lookup(struct clk *clk, unsigned long rate)
{
	int divisor = clk->parent->rate / rate;
	int i;

	for (i = 0; i < ARRAY_SIZE(frqcr3_divisors); i++)
		if (frqcr3_divisors[i] == divisor)
			return frqcr3_values[i];

	/* Safe fallback */
	return 5;
}