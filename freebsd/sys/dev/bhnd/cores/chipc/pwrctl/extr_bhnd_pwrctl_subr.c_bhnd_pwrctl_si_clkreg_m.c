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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct bhnd_chipid {int dummy; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHIPC_CLKC_M2 ; 
 int /*<<< orphan*/  CHIPC_CLKC_M3 ; 
 int /*<<< orphan*/  CHIPC_CLKC_SB ; 
#define  CHIPC_PLL_TYPE3 129 
#define  CHIPC_PLL_TYPE6 128 

bus_size_t
bhnd_pwrctl_si_clkreg_m(const struct bhnd_chipid *cid,
    uint8_t pll_type, uint32_t *fixed_hz)
{
	switch (pll_type) {
	case CHIPC_PLL_TYPE6:
		return (CHIPC_CLKC_M3);
	case CHIPC_PLL_TYPE3:
		return (CHIPC_CLKC_M2);
	default:
		return (CHIPC_CLKC_SB);
	}
}