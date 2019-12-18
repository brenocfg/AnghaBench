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
typedef  unsigned long u64 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long ccu_nkmp_calc_rate(unsigned long parent,
					unsigned long n, unsigned long k,
					unsigned long m, unsigned long p)
{
	u64 rate = parent;

	rate *= n * k;
	do_div(rate, m * p);

	return rate;
}