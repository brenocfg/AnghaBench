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
 int /*<<< orphan*/  PMC970N_NONE ; 
 int ppc970_set_pmc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ppc970_stop_pmc(int cpu, int ri)
{
	return ppc970_set_pmc(cpu, ri, PMC970N_NONE);
}