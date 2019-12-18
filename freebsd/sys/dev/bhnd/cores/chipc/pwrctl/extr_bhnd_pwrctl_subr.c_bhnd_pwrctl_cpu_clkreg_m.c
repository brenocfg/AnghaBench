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
typedef  int uint32_t ;
struct bhnd_chipid {int /*<<< orphan*/  chip_id; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_CHIPID_BCM5365 ; 
 int /*<<< orphan*/  CHIPC_CLKC_M2 ; 
 int /*<<< orphan*/  CHIPC_CLKC_M3 ; 
 int /*<<< orphan*/  CHIPC_CLKC_SB ; 
#define  CHIPC_PLL_TYPE2 133 
#define  CHIPC_PLL_TYPE3 132 
#define  CHIPC_PLL_TYPE4 131 
#define  CHIPC_PLL_TYPE5 130 
#define  CHIPC_PLL_TYPE6 129 
#define  CHIPC_PLL_TYPE7 128 

bus_size_t
bhnd_pwrctl_cpu_clkreg_m(const struct bhnd_chipid *cid,
    uint8_t pll_type, uint32_t *fixed_hz)
{
	switch (pll_type) {
	case CHIPC_PLL_TYPE2:
	case CHIPC_PLL_TYPE4:
	case CHIPC_PLL_TYPE6:
	case CHIPC_PLL_TYPE7:
		return (CHIPC_CLKC_M3);

	case CHIPC_PLL_TYPE5:
		/* fixed 200MHz */
		if (fixed_hz != NULL)
			*fixed_hz = 200 * 1000 * 1000;
		return (0);

	case CHIPC_PLL_TYPE3:
		if (cid->chip_id == BHND_CHIPID_BCM5365) {
			/* fixed 200MHz */
			if (fixed_hz != NULL)
				*fixed_hz = 200 * 1000 * 1000;
			return (0);
		}

		return (CHIPC_CLKC_M2);

	default:
		return (CHIPC_CLKC_SB);
	}
}