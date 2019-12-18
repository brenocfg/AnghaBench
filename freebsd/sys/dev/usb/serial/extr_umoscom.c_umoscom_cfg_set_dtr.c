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
struct umoscom_softc {int sc_mcr; } ;
struct ucom_softc {struct umoscom_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMOSCOM_MCR ; 
 int UMOSCOM_MCR_DTR ; 
 int UMOSCOM_UART_REG ; 
 int /*<<< orphan*/  umoscom_cfg_write (struct umoscom_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
umoscom_cfg_set_dtr(struct ucom_softc *ucom, uint8_t onoff)
{
	struct umoscom_softc *sc = ucom->sc_parent;

	if (onoff)
		sc->sc_mcr |= UMOSCOM_MCR_DTR;
	else
		sc->sc_mcr &= ~UMOSCOM_MCR_DTR;

	umoscom_cfg_write(sc, UMOSCOM_MCR, sc->sc_mcr | UMOSCOM_UART_REG);
}