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
 int /*<<< orphan*/  PRM_RSTCTRL ; 
 int /*<<< orphan*/  prcm_write_4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
am335x_prcm_reset(void)
{
	prcm_write_4(PRM_RSTCTRL, (1<<1));
}