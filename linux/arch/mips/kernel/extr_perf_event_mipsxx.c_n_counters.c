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
#define  CPU_R10000 131 
#define  CPU_R12000 130 
#define  CPU_R14000 129 
#define  CPU_R16000 128 
 int __n_counters () ; 
 int current_cpu_type () ; 

__attribute__((used)) static int n_counters(void)
{
	int counters;

	switch (current_cpu_type()) {
	case CPU_R10000:
		counters = 2;
		break;

	case CPU_R12000:
	case CPU_R14000:
	case CPU_R16000:
		counters = 4;
		break;

	default:
		counters = __n_counters();
	}

	return counters;
}