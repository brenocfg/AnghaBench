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
struct tsec_softc {int tx_ic_count; int tx_ic_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSEC_REG_TXIC ; 
 int /*<<< orphan*/  TSEC_WRITE (struct tsec_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tsec_set_txic(struct tsec_softc *sc)
{
	uint32_t txic_val;

	if (sc->tx_ic_count == 0 || sc->tx_ic_time == 0)
		/* Disable TX IC */
		txic_val = 0;
	else {
		txic_val = 0x80000000;
		txic_val |= (sc->tx_ic_count << 21);
		txic_val |= sc->tx_ic_time;
	}

	TSEC_WRITE(sc, TSEC_REG_TXIC, txic_val);
}