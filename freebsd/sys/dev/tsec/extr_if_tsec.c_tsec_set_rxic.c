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
struct tsec_softc {int rx_ic_count; int rx_ic_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSEC_REG_RXIC ; 
 int /*<<< orphan*/  TSEC_WRITE (struct tsec_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tsec_set_rxic(struct tsec_softc *sc)
{
	uint32_t rxic_val;

	if (sc->rx_ic_count == 0 || sc->rx_ic_time == 0)
		/* Disable RX IC */
		rxic_val = 0;
	else {
		rxic_val = 0x80000000;
		rxic_val |= (sc->rx_ic_count << 21);
		rxic_val |= sc->rx_ic_time;
	}

	TSEC_WRITE(sc, TSEC_REG_RXIC, rxic_val);
}