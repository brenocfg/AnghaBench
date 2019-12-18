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
 unsigned int AIRTIME_QUANTUM_MAX ; 
 unsigned int AIRTIME_QUANTUM_MIN ; 
 unsigned int AIRTIME_QUANTUM_TARGET ; 

__attribute__((used)) static unsigned int get_airtime_quantum(unsigned int max_wt)
{
	unsigned int quantum = AIRTIME_QUANTUM_TARGET / max_wt;

	if (quantum < AIRTIME_QUANTUM_MIN)
		quantum = AIRTIME_QUANTUM_MIN;
	else if (quantum > AIRTIME_QUANTUM_MAX)
		quantum = AIRTIME_QUANTUM_MAX;

	return quantum;
}