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
struct spi_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CH_CFG ; 
 int ENXIO ; 
 int FB_CLK_180 ; 
 int /*<<< orphan*/  FB_CLK_SEL ; 
 int READ4 (struct spi_softc*,int /*<<< orphan*/ ) ; 
 int RX_CH_ON ; 
 int TX_CH_ON ; 
 int /*<<< orphan*/  WRITE4 (struct spi_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 struct spi_softc* spi_sc ; 
 int /*<<< orphan*/  spi_spec ; 

__attribute__((used)) static int
spi_attach(device_t dev)
{
	struct spi_softc *sc;
	int reg;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, spi_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	spi_sc = sc;

	WRITE4(sc, FB_CLK_SEL, FB_CLK_180);

	reg = READ4(sc, CH_CFG);
	reg |= (RX_CH_ON | TX_CH_ON);
	WRITE4(sc, CH_CFG, reg);

	device_add_child(dev, "spibus", 0);
	return (bus_generic_attach(dev));
}