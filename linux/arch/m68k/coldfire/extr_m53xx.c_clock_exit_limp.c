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
 int /*<<< orphan*/  MCF_CCM_MISCCR ; 
 int MCF_CCM_MISCCR_LIMP ; 
 int MCF_CCM_MISCCR_PLL_LOCK ; 
 int get_sys_clock () ; 
 int readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

int clock_exit_limp(void)
{
	int fout;
	
	/* Exit LIMP mode */
	writew(readw(MCF_CCM_MISCCR) & ~MCF_CCM_MISCCR_LIMP, MCF_CCM_MISCCR);

	/* Wait for PLL to lock */
	while (!(readw(MCF_CCM_MISCCR) & MCF_CCM_MISCCR_PLL_LOCK))
		;
	
	fout = get_sys_clock();

	return fout;
}