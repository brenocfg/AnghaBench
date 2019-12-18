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
 int /*<<< orphan*/  DSL_DFE_PMU_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_PMU_ENABLE ; 
 int /*<<< orphan*/  PPE_EMA_PMU_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPE_SLL01_PMU_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPE_TC_PMU_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPE_TPE_PMU_SETUP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void init_pmu(void)
{
    //*(unsigned long *)0xBF10201C &= ~((1 << 15) | (1 << 13) | (1 << 9));
    //PPE_TOP_PMU_SETUP(IFX_PMU_ENABLE);
    PPE_SLL01_PMU_SETUP(IFX_PMU_ENABLE);
    PPE_TC_PMU_SETUP(IFX_PMU_ENABLE);
    PPE_EMA_PMU_SETUP(IFX_PMU_ENABLE);
    //PPE_QSB_PMU_SETUP(IFX_PMU_ENABLE);
    PPE_TPE_PMU_SETUP(IFX_PMU_ENABLE);
    DSL_DFE_PMU_SETUP(IFX_PMU_ENABLE);
}