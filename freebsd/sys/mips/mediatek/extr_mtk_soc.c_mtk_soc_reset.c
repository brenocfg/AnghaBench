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
 int /*<<< orphan*/  SYSCTL_RSTCTRL ; 
 int /*<<< orphan*/  mtk_sysctl_clr_set (int /*<<< orphan*/ ,int,int) ; 

void
mtk_soc_reset(void)
{

	mtk_sysctl_clr_set(SYSCTL_RSTCTRL, 0, 1);
	mtk_sysctl_clr_set(SYSCTL_RSTCTRL, 1, 0);
}