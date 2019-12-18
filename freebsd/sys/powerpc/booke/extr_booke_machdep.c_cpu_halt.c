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

/* Variables and functions */
 int PSL_CE ; 
 int PSL_DE ; 
 int PSL_EE ; 
 int PSL_ME ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 

void
cpu_halt(void)
{

	mtmsr(mfmsr() & ~(PSL_CE | PSL_EE | PSL_ME | PSL_DE));
	while (1)
		;
}