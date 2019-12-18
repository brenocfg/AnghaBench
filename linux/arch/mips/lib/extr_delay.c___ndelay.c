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
struct TYPE_2__ {unsigned int udelay_val; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  __delay (unsigned long) ; 
 TYPE_1__ raw_current_cpu_data ; 

void __ndelay(unsigned long ns)
{
	unsigned int lpj = raw_current_cpu_data.udelay_val;

	__delay((ns * 0x00000005ull * HZ * lpj) >> 32);
}