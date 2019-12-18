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
 int mp_ncpus ; 

void
cpu_mp_setmaxid(void)
{

	/*
	 * mp_ncpus and mp_maxid should be already set by calls to cpu_add().
	 * If there were no calls to cpu_add() assume this is a UP system.
	 */
	if (mp_ncpus == 0)
		mp_ncpus = 1;
}