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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct avr32dci_td {int /*<<< orphan*/  ep_no; int /*<<< orphan*/  pc; } ;
struct avr32dci_softc {int sc_dv_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVR32_EPTSTA (int /*<<< orphan*/ ) ; 
 scalar_t__ AVR32_EPTSTA_BUSY_BANK_STA (int) ; 
 int AVR32_EPTSTA_RX_SETUP ; 
 struct avr32dci_softc* AVR32_PC2SC (int /*<<< orphan*/ ) ; 
 int AVR32_READ_4 (struct avr32dci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  avr32dci_set_address (struct avr32dci_softc*,int) ; 

__attribute__((used)) static uint8_t
avr32dci_data_tx_sync(struct avr32dci_td *td)
{
	struct avr32dci_softc *sc;
	uint32_t temp;

	/* get pointer to softc */
	sc = AVR32_PC2SC(td->pc);

	/* check endpoint status */
	temp = AVR32_READ_4(sc, AVR32_EPTSTA(td->ep_no));

	DPRINTFN(5, "EPTSTA(%u)=0x%08x\n", td->ep_no, temp);

	if (temp & AVR32_EPTSTA_RX_SETUP) {
		DPRINTFN(5, "faking complete\n");
		/* Race condition */
		return (0);		/* complete */
	}
	/*
	 * The control endpoint has only got one bank, so if that bank
	 * is free the packet has been transferred!
	 */
	if (AVR32_EPTSTA_BUSY_BANK_STA(temp) != 0) {
		/* cannot write any data - a bank is busy */
		goto not_complete;
	}
	if (sc->sc_dv_addr != 0xFF) {
		/* set new address */
		avr32dci_set_address(sc, sc->sc_dv_addr);
	}
	return (0);			/* complete */

not_complete:
	return (1);			/* not complete */
}