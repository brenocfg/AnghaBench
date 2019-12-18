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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMX51CLK_PERCLK_ROOT ; 
 int /*<<< orphan*/  imx51_get_clock (int /*<<< orphan*/ ) ; 

uint32_t
imx_ccm_perclk_hz(void)
{

	return (imx51_get_clock(IMX51CLK_PERCLK_ROOT));
}