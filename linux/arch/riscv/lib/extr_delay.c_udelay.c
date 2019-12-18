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
typedef  int u64 ;

/* Variables and functions */
 unsigned long MAX_UDELAY_US ; 
 int UDELAY_MULT ; 
 int UDELAY_SHIFT ; 
 int /*<<< orphan*/  __delay (int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int lpj_fine ; 
 int riscv_timebase ; 
 scalar_t__ unlikely (int) ; 

void udelay(unsigned long usecs)
{
	u64 ucycles = (u64)usecs * lpj_fine * UDELAY_MULT;
	u64 n;

	if (unlikely(usecs > MAX_UDELAY_US)) {
		n = (u64)usecs * riscv_timebase;
		do_div(n, 1000000);

		__delay(n);
		return;
	}

	__delay(ucycles >> UDELAY_SHIFT);
}