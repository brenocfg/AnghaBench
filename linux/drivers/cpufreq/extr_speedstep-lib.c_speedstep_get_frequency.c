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
typedef  enum speedstep_processor { ____Placeholder_speedstep_processor } speedstep_processor ;

/* Variables and functions */
#define  SPEEDSTEP_CPU_P4D 134 
#define  SPEEDSTEP_CPU_P4M 133 
#define  SPEEDSTEP_CPU_PCORE 132 
#define  SPEEDSTEP_CPU_PIII_C 131 
#define  SPEEDSTEP_CPU_PIII_C_EARLY 130 
#define  SPEEDSTEP_CPU_PIII_T 129 
#define  SPEEDSTEP_CPU_PM 128 
 unsigned int pentium3_get_frequency (int) ; 
 unsigned int pentium4_get_frequency () ; 
 unsigned int pentiumM_get_frequency () ; 
 unsigned int pentium_core_get_frequency () ; 

unsigned int speedstep_get_frequency(enum speedstep_processor processor)
{
	switch (processor) {
	case SPEEDSTEP_CPU_PCORE:
		return pentium_core_get_frequency();
	case SPEEDSTEP_CPU_PM:
		return pentiumM_get_frequency();
	case SPEEDSTEP_CPU_P4D:
	case SPEEDSTEP_CPU_P4M:
		return pentium4_get_frequency();
	case SPEEDSTEP_CPU_PIII_T:
	case SPEEDSTEP_CPU_PIII_C:
	case SPEEDSTEP_CPU_PIII_C_EARLY:
		return pentium3_get_frequency(processor);
	default:
		return 0;
	};
	return 0;
}