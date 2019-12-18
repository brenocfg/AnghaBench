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
typedef  int u_int32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int HIFN_PLL_IS ; 
 int HIFN_PLL_ND_SHIFT ; 
 int HIFN_PLL_REF_SEL ; 
#define  PCI_PRODUCT_HIFN_7954 130 
#define  PCI_PRODUCT_HIFN_7955 129 
#define  PCI_PRODUCT_HIFN_7956 128 
 int checkmaxmin (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_string_value (char*,int /*<<< orphan*/ ,char*,char const**) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int strtoul (char const*,char**,int) ; 

__attribute__((used)) static void
hifn_getpllconfig(device_t dev, u_int *pll)
{
	const char *pllspec;
	u_int freq, mul, fl, fh;
	u_int32_t pllconfig;
	char *nxt;

	if (resource_string_value("hifn", device_get_unit(dev),
	    "pllconfig", &pllspec))
		pllspec = "ext66";
	fl = 33, fh = 66;
	pllconfig = 0;
	if (strncmp(pllspec, "ext", 3) == 0) {
		pllspec += 3;
		pllconfig |= HIFN_PLL_REF_SEL;
		switch (pci_get_device(dev)) {
		case PCI_PRODUCT_HIFN_7955:
		case PCI_PRODUCT_HIFN_7956:
			fl = 20, fh = 100;
			break;
#ifdef notyet
		case PCI_PRODUCT_HIFN_7954:
			fl = 20, fh = 66;
			break;
#endif
		}
	} else if (strncmp(pllspec, "pci", 3) == 0)
		pllspec += 3;
	freq = strtoul(pllspec, &nxt, 10);
	if (nxt == pllspec)
		freq = 66;
	else
		freq = checkmaxmin(dev, "frequency", freq, fl, fh);
	/*
	 * Calculate multiplier.  We target a Fck of 266 MHz,
	 * allowing only even values, possibly rounded down.
	 * Multipliers > 8 must set the charge pump current.
	 */
	mul = checkmaxmin(dev, "PLL divisor", (266 / freq) &~ 1, 2, 12);
	pllconfig |= (mul / 2 - 1) << HIFN_PLL_ND_SHIFT;
	if (mul > 8)
		pllconfig |= HIFN_PLL_IS;
	*pll = pllconfig;
}