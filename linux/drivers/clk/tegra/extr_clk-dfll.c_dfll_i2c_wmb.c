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
struct tegra_dfll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLL_I2C_CFG ; 
 int /*<<< orphan*/  dfll_i2c_readl (struct tegra_dfll*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dfll_i2c_wmb(struct tegra_dfll *td)
{
	dfll_i2c_readl(td, DFLL_I2C_CFG);
}