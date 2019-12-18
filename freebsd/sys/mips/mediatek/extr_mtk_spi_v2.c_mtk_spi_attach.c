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
struct mtk_spi_softc {int /*<<< orphan*/  sc_mem_res; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTK_SPIMASTER ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SPI_READ (struct mtk_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_WRITE (struct mtk_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mtk_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mtk_spi_wait (struct mtk_spi_softc*) ; 

__attribute__((used)) static int
mtk_spi_attach(device_t dev)
{
	struct mtk_spi_softc *sc = device_get_softc(dev);
	uint32_t val;
	int rid;

	sc->sc_dev = dev;
        rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (!sc->sc_mem_res) {
		device_printf(dev, "Could not map memory\n");
		return (ENXIO);
	}

	if (mtk_spi_wait(sc)) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);
		return (EBUSY);
	}

	val = SPI_READ(sc, MTK_SPIMASTER);
	val &= ~(0xfff << 16);
	val |= 13 << 16;
	val |= 7 << 29;
	val |= 1 << 2;
	SPI_WRITE(sc, MTK_SPIMASTER, val);
	    /*
	     * W25Q64CV max 104MHz, bus 120-192 MHz, so divide by 2.
	     * Update: divide by 4, DEV2 to fast for flash.
	     */

	device_add_child(dev, "spibus", 0);
	return (bus_generic_attach(dev));
}