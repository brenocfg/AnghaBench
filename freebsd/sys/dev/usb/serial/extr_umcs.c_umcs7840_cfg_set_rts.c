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
struct TYPE_2__ {int /*<<< orphan*/  sc_mcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,size_t,char*) ; 
 int /*<<< orphan*/  MCS7840_UART_MCR_RTS ; 
 int /*<<< orphan*/  MCS7840_UART_REG_MCR ; 
 int /*<<< orphan*/  umcs7840_set_UART_reg_sync (struct umcs7840_softc*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
umcs7840_cfg_set_rts(struct ucom_softc *ucom, uint8_t onoff)
{
	struct umcs7840_softc *sc = ucom->sc_parent;
	uint8_t pn = ucom->sc_portno;

	if (onoff)
		sc->sc_ports[pn].sc_mcr |= MCS7840_UART_MCR_RTS;
	else
		sc->sc_ports[pn].sc_mcr &= ~MCS7840_UART_MCR_RTS;

	umcs7840_set_UART_reg_sync(sc, pn, MCS7840_UART_REG_MCR, sc->sc_ports[pn].sc_mcr);
	DPRINTF("Port %d RTS set to: %s\n", pn, onoff ? "on" : "off");
}