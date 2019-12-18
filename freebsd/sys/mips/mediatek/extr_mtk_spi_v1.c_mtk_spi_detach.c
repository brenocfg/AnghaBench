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
struct mtk_spi_softc {scalar_t__ sc_mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CS_HIGH ; 
 int HIZSMOSI ; 
 int /*<<< orphan*/  MTK_SPICTL ; 
 int /*<<< orphan*/  SPI_SET_BITS (struct mtk_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct mtk_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_spi_detach(device_t dev)
{
	struct mtk_spi_softc *sc = device_get_softc(dev);

	SPI_SET_BITS(sc, MTK_SPICTL, HIZSMOSI | CS_HIGH);

	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);

	return (0);
}