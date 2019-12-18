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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  __udelay (unsigned long long) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 scalar_t__ get_tod_clock_fast () ; 

void __ndelay(unsigned long long nsecs)
{
	u64 end;

	nsecs <<= 9;
	do_div(nsecs, 125);
	end = get_tod_clock_fast() + nsecs;
	if (nsecs & ~0xfffUL)
		__udelay(nsecs >> 12);
	while (get_tod_clock_fast() < end)
		barrier();
}