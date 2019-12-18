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
struct TYPE_3__ {int max_freq; int turbo_freq; } ;
struct cpudata {TYPE_1__ pstate; } ;
struct TYPE_4__ {scalar_t__ no_turbo; scalar_t__ turbo_disabled; } ;

/* Variables and functions */
 TYPE_2__ global ; 

__attribute__((used)) static int intel_pstate_get_max_freq(struct cpudata *cpu)
{
	return global.turbo_disabled || global.no_turbo ?
			cpu->pstate.max_freq : cpu->pstate.turbo_freq;
}