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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ EXYNOS4_MCT_G_TCON ; 
 int /*<<< orphan*/  MCT_G_TCON_START ; 
 int /*<<< orphan*/  exynos4_mct_write (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 scalar_t__ reg_base ; 

__attribute__((used)) static void exynos4_mct_frc_start(void)
{
	u32 reg;

	reg = readl_relaxed(reg_base + EXYNOS4_MCT_G_TCON);
	reg |= MCT_G_TCON_START;
	exynos4_mct_write(reg, EXYNOS4_MCT_G_TCON);
}