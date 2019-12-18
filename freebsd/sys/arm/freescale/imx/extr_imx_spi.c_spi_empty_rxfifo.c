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
struct spi_softc {scalar_t__ rxidx; scalar_t__ rxlen; int /*<<< orphan*/  fifocnt; scalar_t__* rxbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECSPI_RXDATA ; 
 int /*<<< orphan*/  ECSPI_STATREG ; 
 int RD4 (struct spi_softc*,int /*<<< orphan*/ ) ; 
 int SREG_RR ; 

__attribute__((used)) static void
spi_empty_rxfifo(struct spi_softc *sc)
{

	while (sc->rxidx < sc->rxlen && (RD4(sc, ECSPI_STATREG) & SREG_RR)) {
		sc->rxbuf[sc->rxidx++] = (uint8_t)RD4(sc, ECSPI_RXDATA);
		--sc->fifocnt;
	}
}