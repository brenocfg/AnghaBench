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
typedef  int u32 ;
typedef  enum index { ____Placeholder_index } index ;

/* Variables and functions */
 int INDEX_ERROR ; 
 int INDEX_FIVE ; 
 int INDEX_FOUR ; 
 int INDEX_ONE ; 
 int INDEX_THREE ; 
 int INDEX_TWO ; 
 int INDEX_ZERO ; 
#define  MSR_F15H_PERF_CTL0 147 
#define  MSR_F15H_PERF_CTL1 146 
#define  MSR_F15H_PERF_CTL2 145 
#define  MSR_F15H_PERF_CTL3 144 
#define  MSR_F15H_PERF_CTL4 143 
#define  MSR_F15H_PERF_CTL5 142 
#define  MSR_F15H_PERF_CTR0 141 
#define  MSR_F15H_PERF_CTR1 140 
#define  MSR_F15H_PERF_CTR2 139 
#define  MSR_F15H_PERF_CTR3 138 
#define  MSR_F15H_PERF_CTR4 137 
#define  MSR_F15H_PERF_CTR5 136 
#define  MSR_K7_EVNTSEL0 135 
#define  MSR_K7_EVNTSEL1 134 
#define  MSR_K7_EVNTSEL2 133 
#define  MSR_K7_EVNTSEL3 132 
#define  MSR_K7_PERFCTR0 131 
#define  MSR_K7_PERFCTR1 130 
#define  MSR_K7_PERFCTR2 129 
#define  MSR_K7_PERFCTR3 128 

__attribute__((used)) static enum index msr_to_index(u32 msr)
{
	switch (msr) {
	case MSR_F15H_PERF_CTL0:
	case MSR_F15H_PERF_CTR0:
	case MSR_K7_EVNTSEL0:
	case MSR_K7_PERFCTR0:
		return INDEX_ZERO;
	case MSR_F15H_PERF_CTL1:
	case MSR_F15H_PERF_CTR1:
	case MSR_K7_EVNTSEL1:
	case MSR_K7_PERFCTR1:
		return INDEX_ONE;
	case MSR_F15H_PERF_CTL2:
	case MSR_F15H_PERF_CTR2:
	case MSR_K7_EVNTSEL2:
	case MSR_K7_PERFCTR2:
		return INDEX_TWO;
	case MSR_F15H_PERF_CTL3:
	case MSR_F15H_PERF_CTR3:
	case MSR_K7_EVNTSEL3:
	case MSR_K7_PERFCTR3:
		return INDEX_THREE;
	case MSR_F15H_PERF_CTL4:
	case MSR_F15H_PERF_CTR4:
		return INDEX_FOUR;
	case MSR_F15H_PERF_CTL5:
	case MSR_F15H_PERF_CTR5:
		return INDEX_FIVE;
	default:
		return INDEX_ERROR;
	}
}