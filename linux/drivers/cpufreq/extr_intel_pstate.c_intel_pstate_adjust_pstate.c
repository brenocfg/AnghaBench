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
struct sample {int busy_scaled; int /*<<< orphan*/  tsc; int /*<<< orphan*/  aperf; int /*<<< orphan*/  mperf; int /*<<< orphan*/  core_avg_perf; } ;
struct TYPE_2__ {int current_pstate; int scaling; } ;
struct cpudata {int iowait_boost; TYPE_1__ pstate; struct sample sample; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  fp_toint (int) ; 
 int /*<<< orphan*/  get_avg_frequency (struct cpudata*) ; 
 int get_target_pstate (struct cpudata*) ; 
 int intel_pstate_prepare_request (struct cpudata*,int) ; 
 int /*<<< orphan*/  intel_pstate_update_pstate (struct cpudata*,int) ; 
 int /*<<< orphan*/  mul_ext_fp (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cpu_frequency (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_pstate_sample (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_turbo_state () ; 

__attribute__((used)) static void intel_pstate_adjust_pstate(struct cpudata *cpu)
{
	int from = cpu->pstate.current_pstate;
	struct sample *sample;
	int target_pstate;

	update_turbo_state();

	target_pstate = get_target_pstate(cpu);
	target_pstate = intel_pstate_prepare_request(cpu, target_pstate);
	trace_cpu_frequency(target_pstate * cpu->pstate.scaling, cpu->cpu);
	intel_pstate_update_pstate(cpu, target_pstate);

	sample = &cpu->sample;
	trace_pstate_sample(mul_ext_fp(100, sample->core_avg_perf),
		fp_toint(sample->busy_scaled),
		from,
		cpu->pstate.current_pstate,
		sample->mperf,
		sample->aperf,
		sample->tsc,
		get_avg_frequency(cpu),
		fp_toint(cpu->iowait_boost * 100));
}