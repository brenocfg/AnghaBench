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
struct pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XTENSA_PMU_PMG ; 
 int XTENSA_PMU_PMG_PMEN ; 
 int get_er (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_er (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xtensa_pmu_disable(struct pmu *pmu)
{
	set_er(get_er(XTENSA_PMU_PMG) & ~XTENSA_PMU_PMG_PMEN, XTENSA_PMU_PMG);
}