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
struct anadig_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ANADIG_PLL1_CTRL ; 
 int /*<<< orphan*/  ANADIG_PLL2_CTRL ; 
 int /*<<< orphan*/  ANADIG_PLL3_CTRL ; 
 int /*<<< orphan*/  ANADIG_PLL4_CTRL ; 
 int /*<<< orphan*/  ANADIG_PLL5_CTRL ; 
 int /*<<< orphan*/  ANADIG_PLL6_CTRL ; 
 int /*<<< orphan*/  ANADIG_PLL7_CTRL ; 
 int /*<<< orphan*/  ANADIG_REG_3P0 ; 
 int ENABLE_LINREG ; 
 int ENXIO ; 
 int EN_CLK_TO_UTMI ; 
 int READ4 (struct anadig_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_ANALOG_USB_MISC (int) ; 
 int /*<<< orphan*/  USB_MISC (int) ; 
 int /*<<< orphan*/  WRITE4 (struct anadig_softc*,int /*<<< orphan*/ ,int) ; 
 struct anadig_softc* anadig_sc ; 
 int /*<<< orphan*/  anadig_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct anadig_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  enable_pll (struct anadig_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
anadig_attach(device_t dev)
{
	struct anadig_softc *sc;
	int reg;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, anadig_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	anadig_sc = sc;

	/* Enable USB PLLs */
	enable_pll(sc, ANADIG_PLL3_CTRL);
	enable_pll(sc, ANADIG_PLL7_CTRL);

	/* Enable other PLLs */
	enable_pll(sc, ANADIG_PLL1_CTRL);
	enable_pll(sc, ANADIG_PLL2_CTRL);
	enable_pll(sc, ANADIG_PLL4_CTRL);
	enable_pll(sc, ANADIG_PLL5_CTRL);
	enable_pll(sc, ANADIG_PLL6_CTRL);

	/* Enable USB voltage regulator */
	reg = READ4(sc, ANADIG_REG_3P0);
	reg |= (ENABLE_LINREG);
	WRITE4(sc, ANADIG_REG_3P0, reg);

	/* Give clocks to USB */
	reg = READ4(sc, USB_MISC(0));
	reg |= (EN_CLK_TO_UTMI);
	WRITE4(sc, USB_MISC(0), reg);

	reg = READ4(sc, USB_MISC(1));
	reg |= (EN_CLK_TO_UTMI);
	WRITE4(sc, USB_MISC(1), reg);

#if 0
	printf("USB_ANALOG_USB_MISC(0) == 0x%08x\n",
	    READ4(sc, USB_ANALOG_USB_MISC(0)));
	printf("USB_ANALOG_USB_MISC(1) == 0x%08x\n",
	    READ4(sc, USB_ANALOG_USB_MISC(1)));
#endif

	return (0);
}