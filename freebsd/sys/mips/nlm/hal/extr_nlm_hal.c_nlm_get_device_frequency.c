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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int u_int ;

/* Variables and functions */
 int DFS_DEVICE_NAE ; 
 int /*<<< orphan*/  SYS_DFS_DIV_VALUE0 ; 
 int /*<<< orphan*/  SYS_DFS_DIV_VALUE1 ; 
 int /*<<< orphan*/  SYS_PLL_CTRL ; 
 int /*<<< orphan*/  nlm_is_xlp8xx_ax () ; 
 int nlm_read_sys_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
nlm_get_device_frequency(uint64_t sysbase, int devtype)
{
	uint32_t pllctrl, dfsdiv, spf, spr, div_val;
	int extra_div;

	pllctrl = nlm_read_sys_reg(sysbase, SYS_PLL_CTRL);
	if (devtype <= 7)
		div_val = nlm_read_sys_reg(sysbase, SYS_DFS_DIV_VALUE0);
	else {
		devtype -= 8;
		div_val = nlm_read_sys_reg(sysbase, SYS_DFS_DIV_VALUE1);
	}
	dfsdiv = ((div_val >> (devtype << 2)) & 0xf) + 1;
	spf = (pllctrl >> 3 & 0x7f) + 1;
	spr = (pllctrl >> 1 & 0x03) + 1;
	if (devtype == DFS_DEVICE_NAE && !nlm_is_xlp8xx_ax())
		extra_div = 2;
	else
		extra_div = 1;

	return ((400 * spf) / (3 * extra_div * spr * dfsdiv));
}