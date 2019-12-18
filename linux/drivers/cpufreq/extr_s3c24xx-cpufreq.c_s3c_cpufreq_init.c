#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  transition_latency; } ;
struct cpufreq_policy {int /*<<< orphan*/  freq_table; TYPE_1__ cpuinfo; int /*<<< orphan*/  clk; } ;
struct TYPE_6__ {TYPE_2__* info; } ;
struct TYPE_5__ {int /*<<< orphan*/  latency; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_arm ; 
 TYPE_3__ cpu_cur ; 
 int /*<<< orphan*/  ftab ; 

__attribute__((used)) static int s3c_cpufreq_init(struct cpufreq_policy *policy)
{
	policy->clk = clk_arm;
	policy->cpuinfo.transition_latency = cpu_cur.info->latency;
	policy->freq_table = ftab;

	return 0;
}