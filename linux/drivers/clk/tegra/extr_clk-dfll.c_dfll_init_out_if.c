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
typedef  unsigned long u32 ;
struct tegra_dfll {int lut_min; int lut_bottom; unsigned long lut_max; unsigned long lut_size; int lut_safe; scalar_t__ pmu_if; unsigned long reg_init_uV; unsigned long* lut_uv; TYPE_2__* soc; } ;
struct TYPE_3__ {int step_uv; } ;
struct TYPE_4__ {TYPE_1__ alignment; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLL_INTR_EN ; 
 int DFLL_INTR_MAX_MASK ; 
 int DFLL_INTR_MIN_MASK ; 
 int /*<<< orphan*/  DFLL_INTR_STS ; 
 int /*<<< orphan*/  DFLL_OUTPUT_CFG ; 
 unsigned long DFLL_OUTPUT_CFG_MAX_SHIFT ; 
 unsigned long DFLL_OUTPUT_CFG_MIN_SHIFT ; 
 unsigned long DFLL_OUTPUT_CFG_SAFE_SHIFT ; 
 int /*<<< orphan*/  DFLL_OUTPUT_FORCE ; 
 unsigned int DIV_ROUND_UP (unsigned long,int) ; 
 scalar_t__ TEGRA_DFLL_PMU_PWM ; 
 int /*<<< orphan*/  dfll_force_output (struct tegra_dfll*,unsigned int) ; 
 int /*<<< orphan*/  dfll_i2c_writel (struct tegra_dfll*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfll_init_i2c_if (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_load_i2c_lut (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_wmb (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_writel (struct tegra_dfll*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dfll_init_out_if(struct tegra_dfll *td)
{
	u32 val;

	td->lut_min = td->lut_bottom;
	td->lut_max = td->lut_size - 1;
	td->lut_safe = td->lut_min + (td->lut_min < td->lut_max ? 1 : 0);

	/* clear DFLL_OUTPUT_CFG before setting new value */
	dfll_writel(td, 0, DFLL_OUTPUT_CFG);
	dfll_wmb(td);

	val = (td->lut_safe << DFLL_OUTPUT_CFG_SAFE_SHIFT) |
	      (td->lut_max << DFLL_OUTPUT_CFG_MAX_SHIFT) |
	      (td->lut_min << DFLL_OUTPUT_CFG_MIN_SHIFT);
	dfll_writel(td, val, DFLL_OUTPUT_CFG);
	dfll_wmb(td);

	dfll_writel(td, 0, DFLL_OUTPUT_FORCE);
	dfll_i2c_writel(td, 0, DFLL_INTR_EN);
	dfll_i2c_writel(td, DFLL_INTR_MAX_MASK | DFLL_INTR_MIN_MASK,
			DFLL_INTR_STS);

	if (td->pmu_if == TEGRA_DFLL_PMU_PWM) {
		u32 vinit = td->reg_init_uV;
		int vstep = td->soc->alignment.step_uv;
		unsigned long vmin = td->lut_uv[0];

		/* set initial voltage */
		if ((vinit >= vmin) && vstep) {
			unsigned int vsel;

			vsel = DIV_ROUND_UP((vinit - vmin), vstep);
			dfll_force_output(td, vsel);
		}
	} else {
		dfll_load_i2c_lut(td);
		dfll_init_i2c_if(td);
	}
}