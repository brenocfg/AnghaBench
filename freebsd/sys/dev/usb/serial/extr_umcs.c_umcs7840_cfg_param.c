#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct umcs7840_softc {TYPE_1__* sc_ports; } ;
struct ucom_softc {size_t sc_portno; struct umcs7840_softc* sc_parent; } ;
struct termios {int c_cflag; int /*<<< orphan*/  c_ospeed; } ;
struct TYPE_2__ {size_t sc_lcr; size_t sc_mcr; } ;

/* Variables and functions */
 int CDSR_OFLOW ; 
 int CDTR_IFLOW ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 size_t MCS7840_UART_LCR_DATALEN5 ; 
 size_t MCS7840_UART_LCR_DATALEN6 ; 
 size_t MCS7840_UART_LCR_DATALEN7 ; 
 size_t MCS7840_UART_LCR_DATALEN8 ; 
 size_t MCS7840_UART_LCR_DATALENMASK ; 
 size_t MCS7840_UART_LCR_PARITYEVEN ; 
 size_t MCS7840_UART_LCR_PARITYMASK ; 
 size_t MCS7840_UART_LCR_PARITYODD ; 
 size_t MCS7840_UART_LCR_PARITYON ; 
 size_t MCS7840_UART_LCR_STOPB1 ; 
 size_t MCS7840_UART_LCR_STOPB2 ; 
 size_t MCS7840_UART_MCR_CTSRTS ; 
 size_t MCS7840_UART_MCR_DTRDSR ; 
 int /*<<< orphan*/  MCS7840_UART_REG_LCR ; 
 int /*<<< orphan*/  MCS7840_UART_REG_MCR ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  umcs7840_set_UART_reg_sync (struct umcs7840_softc*,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  umcs7840_set_baudrate (struct umcs7840_softc*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
umcs7840_cfg_param(struct ucom_softc *ucom, struct termios *t)
{
	struct umcs7840_softc *sc = ucom->sc_parent;
	uint8_t pn = ucom->sc_portno;
	uint8_t lcr = sc->sc_ports[pn].sc_lcr;
	uint8_t mcr = sc->sc_ports[pn].sc_mcr;

	DPRINTF("Port %d config:\n", pn);
	if (t->c_cflag & CSTOPB) {
		DPRINTF("  2 stop bits\n");
		lcr |= MCS7840_UART_LCR_STOPB2;
	} else {
		lcr |= MCS7840_UART_LCR_STOPB1;
		DPRINTF("  1 stop bit\n");
	}

	lcr &= ~MCS7840_UART_LCR_PARITYMASK;
	if (t->c_cflag & PARENB) {
		lcr |= MCS7840_UART_LCR_PARITYON;
		if (t->c_cflag & PARODD) {
			lcr = MCS7840_UART_LCR_PARITYODD;
			DPRINTF("  parity on - odd\n");
		} else {
			lcr = MCS7840_UART_LCR_PARITYEVEN;
			DPRINTF("  parity on - even\n");
		}
	} else {
		lcr &= ~MCS7840_UART_LCR_PARITYON;
		DPRINTF("  parity off\n");
	}

	lcr &= ~MCS7840_UART_LCR_DATALENMASK;
	switch (t->c_cflag & CSIZE) {
	case CS5:
		lcr |= MCS7840_UART_LCR_DATALEN5;
		DPRINTF("  5 bit\n");
		break;
	case CS6:
		lcr |= MCS7840_UART_LCR_DATALEN6;
		DPRINTF("  6 bit\n");
		break;
	case CS7:
		lcr |= MCS7840_UART_LCR_DATALEN7;
		DPRINTF("  7 bit\n");
		break;
	case CS8:
		lcr |= MCS7840_UART_LCR_DATALEN8;
		DPRINTF("  8 bit\n");
		break;
	}

	if (t->c_cflag & CRTSCTS) {
		mcr |= MCS7840_UART_MCR_CTSRTS;
		DPRINTF("  CTS/RTS\n");
	} else
		mcr &= ~MCS7840_UART_MCR_CTSRTS;

	if (t->c_cflag & (CDTR_IFLOW | CDSR_OFLOW)) {
		mcr |= MCS7840_UART_MCR_DTRDSR;
		DPRINTF("  DTR/DSR\n");
	} else
		mcr &= ~MCS7840_UART_MCR_DTRDSR;

	sc->sc_ports[pn].sc_lcr = lcr;
	umcs7840_set_UART_reg_sync(sc, pn, MCS7840_UART_REG_LCR, sc->sc_ports[pn].sc_lcr);
	DPRINTF("Port %d LCR=%02x\n", pn, sc->sc_ports[pn].sc_lcr);

	sc->sc_ports[pn].sc_mcr = mcr;
	umcs7840_set_UART_reg_sync(sc, pn, MCS7840_UART_REG_MCR, sc->sc_ports[pn].sc_mcr);
	DPRINTF("Port %d MCR=%02x\n", pn, sc->sc_ports[pn].sc_mcr);

	umcs7840_set_baudrate(sc, pn, t->c_ospeed);
}