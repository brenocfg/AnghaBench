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
struct TYPE_4__ {int /*<<< orphan*/  core_avg_perf; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_pstate_physical; } ;
struct cpudata {TYPE_2__ sample; TYPE_1__ pstate; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mul_ext_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int32_t get_avg_pstate(struct cpudata *cpu)
{
	return mul_ext_fp(cpu->pstate.max_pstate_physical,
			  cpu->sample.core_avg_perf);
}