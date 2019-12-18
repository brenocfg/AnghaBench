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
struct TYPE_2__ {int /*<<< orphan*/  frequency; } ;
struct s3c_cpufreq_config {TYPE_1__ pll; int /*<<< orphan*/  mpll; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void s3c2410_set_fvco(struct s3c_cpufreq_config *cfg)
{
	if (!IS_ERR(cfg->mpll))
		clk_set_rate(cfg->mpll, cfg->pll.frequency);
}