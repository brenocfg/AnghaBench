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
typedef  int uint32_t ;
struct spi_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CR_MASTER ; 
 int CR_MSS ; 
 int CR_RST_RX ; 
 int CR_RST_TX ; 
 int CR_SPE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  SPI_CR ; 
 int /*<<< orphan*/  SPI_DGIER ; 
 int /*<<< orphan*/  SPI_SRR ; 
 int SRR_RESET ; 
 int /*<<< orphan*/  WRITE4 (struct spi_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_spec ; 

__attribute__((used)) static int
spi_attach(device_t dev)
{
	struct spi_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, spi_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	/* Reset */
	WRITE4(sc, SPI_SRR, SRR_RESET);

	DELAY(1000);

	reg = (CR_MASTER | CR_MSS | CR_RST_RX | CR_RST_TX);
	WRITE4(sc, SPI_CR, reg);
	WRITE4(sc, SPI_DGIER, 0);	/* Disable interrupts */

	reg = (CR_MASTER | CR_MSS | CR_SPE);
	WRITE4(sc, SPI_CR, reg);

	device_add_child(dev, "spibus", 0);
	return (bus_generic_attach(dev));
}