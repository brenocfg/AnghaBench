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
typedef  scalar_t__ u32 ;
struct tegra_dfll {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DFLL_I2C_CFG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __raw_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void dfll_writel(struct tegra_dfll *td, u32 val, u32 offs)
{
	WARN_ON(offs >= DFLL_I2C_CFG);
	__raw_writel(val, td->base + offs);
}