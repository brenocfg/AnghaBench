#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {scalar_t__ max_pstate; scalar_t__ turbo_pstate; } ;
struct cpudata {TYPE_1__ pstate; } ;
struct TYPE_4__ {int turbo_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE ; 
 int MSR_IA32_MISC_ENABLE_TURBO_DISABLE ; 
 struct cpudata** all_cpu_data ; 
 TYPE_2__ global ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void update_turbo_state(void)
{
	u64 misc_en;
	struct cpudata *cpu;

	cpu = all_cpu_data[0];
	rdmsrl(MSR_IA32_MISC_ENABLE, misc_en);
	global.turbo_disabled =
		(misc_en & MSR_IA32_MISC_ENABLE_TURBO_DISABLE ||
		 cpu->pstate.max_pstate == cpu->pstate.turbo_pstate);
}