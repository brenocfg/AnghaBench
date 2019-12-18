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
struct TYPE_2__ {int low; int high; int grew; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_THRM1 ; 
 int /*<<< orphan*/  SPRN_THRM2 ; 
 unsigned int THRM1_TIN ; 
 unsigned int THRM1_TIV ; 
 unsigned int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  set_thresholds (int) ; 
 int step_size ; 
 TYPE_1__* tau ; 
 int window_expand ; 

__attribute__((used)) static void TAUupdate(int cpu)
{
	unsigned thrm;

#ifdef DEBUG
	printk("TAUupdate ");
#endif

	/* if both thresholds are crossed, the step_sizes cancel out
	 * and the window winds up getting expanded twice. */
	if((thrm = mfspr(SPRN_THRM1)) & THRM1_TIV){ /* is valid? */
		if(thrm & THRM1_TIN){ /* crossed low threshold */
			if (tau[cpu].low >= step_size){
				tau[cpu].low -= step_size;
				tau[cpu].high -= (step_size - window_expand);
			}
			tau[cpu].grew = 1;
#ifdef DEBUG
			printk("low threshold crossed ");
#endif
		}
	}
	if((thrm = mfspr(SPRN_THRM2)) & THRM1_TIV){ /* is valid? */
		if(thrm & THRM1_TIN){ /* crossed high threshold */
			if (tau[cpu].high <= 127-step_size){
				tau[cpu].low += (step_size - window_expand);
				tau[cpu].high += step_size;
			}
			tau[cpu].grew = 1;
#ifdef DEBUG
			printk("high threshold crossed ");
#endif
		}
	}

#ifdef DEBUG
	printk("grew = %d\n", tau[cpu].grew);
#endif

#ifndef CONFIG_TAU_INT /* tau_timeout will do this if not using interrupts */
	set_thresholds(cpu);
#endif

}