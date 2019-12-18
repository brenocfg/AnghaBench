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
struct imc_pmu_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_nest_imc_refc ; 
 struct imc_pmu_ref* per_cpu (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct imc_pmu_ref *get_nest_pmu_ref(int cpu)
{
	return per_cpu(local_nest_imc_refc, cpu);
}