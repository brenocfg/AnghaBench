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
struct jme_softc {int /*<<< orphan*/  jme_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int JME_TIMEOUT ; 
 int /*<<< orphan*/  JME_TXCSR ; 
 int TXCSR_TX_ENB ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
jme_stop_tx(struct jme_softc *sc)
{
	uint32_t reg;
	int i;

	reg = CSR_READ_4(sc, JME_TXCSR);
	if ((reg & TXCSR_TX_ENB) == 0)
		return;
	reg &= ~TXCSR_TX_ENB;
	CSR_WRITE_4(sc, JME_TXCSR, reg);
	for (i = JME_TIMEOUT; i > 0; i--) {
		DELAY(1);
		if ((CSR_READ_4(sc, JME_TXCSR) & TXCSR_TX_ENB) == 0)
			break;
	}
	if (i == 0)
		device_printf(sc->jme_dev, "stopping transmitter timeout!\n");
}