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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct rk_spi_softc {scalar_t__ rxidx; scalar_t__ rxlen; scalar_t__* rxbuf; } ;

/* Variables and functions */
 scalar_t__ RK_SPI_READ_4 (struct rk_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK_SPI_RXDR ; 
 int /*<<< orphan*/  RK_SPI_RXFLR ; 

__attribute__((used)) static void
rk_spi_empty_rxfifo(struct rk_spi_softc *sc)
{
	uint32_t rxlevel;
	rxlevel = RK_SPI_READ_4(sc, RK_SPI_RXFLR);
	while (sc->rxidx < sc->rxlen &&
	    (rxlevel-- > 0)) {
		sc->rxbuf[sc->rxidx++] = (uint8_t)RK_SPI_READ_4(sc, RK_SPI_RXDR);
	}
}