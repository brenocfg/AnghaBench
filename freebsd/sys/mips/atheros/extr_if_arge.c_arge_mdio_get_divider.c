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
typedef  unsigned long uint32_t ;
struct arge_softc {int dummy; } ;

/* Variables and functions */
#define  AR71XX_SOC_AR7240 139 
#define  AR71XX_SOC_AR7241 138 
#define  AR71XX_SOC_AR7242 137 
#define  AR71XX_SOC_AR9330 136 
#define  AR71XX_SOC_AR9331 135 
#define  AR71XX_SOC_AR9341 134 
#define  AR71XX_SOC_AR9342 133 
#define  AR71XX_SOC_AR9344 132 
#define  AR71XX_SOC_QCA9533 131 
#define  AR71XX_SOC_QCA9533_V2 130 
#define  AR71XX_SOC_QCA9556 129 
#define  AR71XX_SOC_QCA9558 128 
 int /*<<< orphan*/  ARGEDEBUG (struct arge_softc*,int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ARGE_DBG_RESET ; 
 int EINVAL ; 
 int ENOENT ; 
 unsigned long* ar71xx_mdio_div_table ; 
 unsigned long ar71xx_mdio_freq () ; 
 int ar71xx_soc ; 
 unsigned long* ar7240_mdio_div_table ; 
 unsigned long* ar933x_mdio_div_table ; 
 int nitems (unsigned long*) ; 

__attribute__((used)) static int
arge_mdio_get_divider(struct arge_softc *sc, unsigned long mdio_clock)
{
	unsigned long ref_clock, t;
	const uint32_t *table;
	int ndivs;
	int i;

	/*
	 * This is the base MDIO frequency on the SoC.
	 * The dividers .. well, divide. Duh.
	 */
	ref_clock = ar71xx_mdio_freq();

	/*
	 * If either clock is undefined, just tell the
	 * caller to fall through to the defaults.
	 */
	if (ref_clock == 0 || mdio_clock == 0)
		return (-EINVAL);

	/*
	 * Pick the correct table!
	 */
	switch (ar71xx_soc) {
	case AR71XX_SOC_AR9330:
	case AR71XX_SOC_AR9331:
	case AR71XX_SOC_AR9341:
	case AR71XX_SOC_AR9342:
	case AR71XX_SOC_AR9344:
	case AR71XX_SOC_QCA9533:
	case AR71XX_SOC_QCA9533_V2:
	case AR71XX_SOC_QCA9556:
	case AR71XX_SOC_QCA9558:
		table = ar933x_mdio_div_table;
		ndivs = nitems(ar933x_mdio_div_table);
		break;

	case AR71XX_SOC_AR7240:
	case AR71XX_SOC_AR7241:
	case AR71XX_SOC_AR7242:
		table = ar7240_mdio_div_table;
		ndivs = nitems(ar7240_mdio_div_table);
		break;

	default:
		table = ar71xx_mdio_div_table;
		ndivs = nitems(ar71xx_mdio_div_table);
	}

	/*
	 * Now, walk through the list and find the first divisor
	 * that falls under the target MDIO frequency.
	 *
	 * The divisors go up, but the corresponding frequencies
	 * are actually decreasing.
	 */
	for (i = 0; i < ndivs; i++) {
		t = ref_clock / table[i];
		if (t <= mdio_clock) {
			return (i);
		}
	}

	ARGEDEBUG(sc, ARGE_DBG_RESET,
	    "No divider found; MDIO=%lu Hz; target=%lu Hz\n",
		ref_clock, mdio_clock);
	return (-ENOENT);
}