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
struct umct_softc {int sc_mcr; } ;
struct ucom_softc {struct umct_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMCT_SET_MCR ; 
 int /*<<< orphan*/  UMCT_SET_MCR_SIZE ; 
 int /*<<< orphan*/  umct_cfg_do_request (struct umct_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
umct_cfg_set_rts(struct ucom_softc *ucom, uint8_t onoff)
{
	struct umct_softc *sc = ucom->sc_parent;

	if (onoff)
		sc->sc_mcr |= 0x02;
	else
		sc->sc_mcr &= ~0x02;

	umct_cfg_do_request(sc, UMCT_SET_MCR, UMCT_SET_MCR_SIZE, sc->sc_mcr);
}