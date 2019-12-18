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
struct atmegadci_td {int ep_no; int /*<<< orphan*/  pc; } ;
struct atmegadci_softc {int sc_dv_addr; } ;

/* Variables and functions */
 struct atmegadci_softc* ATMEGA_PC2SC (int /*<<< orphan*/ ) ; 
 int ATMEGA_READ_1 (struct atmegadci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATMEGA_UEIENX ; 
 int ATMEGA_UEIENX_RXSTPE ; 
 int ATMEGA_UEIENX_TXINE ; 
 int /*<<< orphan*/  ATMEGA_UEINTX ; 
 int ATMEGA_UEINTX_RXSTPI ; 
 int /*<<< orphan*/  ATMEGA_UENUM ; 
 int /*<<< orphan*/  ATMEGA_UESTA0X ; 
 int /*<<< orphan*/  ATMEGA_WRITE_1 (struct atmegadci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  atmegadci_set_address (struct atmegadci_softc*,int) ; 

__attribute__((used)) static uint8_t
atmegadci_data_tx_sync(struct atmegadci_td *td)
{
	struct atmegadci_softc *sc;
	uint8_t temp;

	/* get pointer to softc */
	sc = ATMEGA_PC2SC(td->pc);

	/* select endpoint number */
	ATMEGA_WRITE_1(sc, ATMEGA_UENUM, td->ep_no);

	/* check endpoint status */
	temp = ATMEGA_READ_1(sc, ATMEGA_UEINTX);

	DPRINTFN(5, "temp=0x%02x\n", temp);

	if (temp & ATMEGA_UEINTX_RXSTPI) {
		DPRINTFN(5, "faking complete\n");
		/* Race condition */
		return (0);		/* complete */
	}
	/*
	 * The control endpoint has only got one bank, so if that bank
	 * is free the packet has been transferred!
	 */
	temp = ATMEGA_READ_1(sc, ATMEGA_UESTA0X);
	if (temp & 3) {
		/* cannot write any data - a bank is busy */
		goto not_complete;
	}
	if (sc->sc_dv_addr != 0xFF) {
		/* set new address */
		atmegadci_set_address(sc, sc->sc_dv_addr);
	}
	return (0);			/* complete */

not_complete:
	/* we only want to know if there is a SETUP packet or free IN packet */
	ATMEGA_WRITE_1(sc, ATMEGA_UEIENX,
	    ATMEGA_UEIENX_RXSTPE | ATMEGA_UEIENX_TXINE);
	return (1);			/* not complete */
}