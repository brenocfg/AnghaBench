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
struct uvscom_softc {int /*<<< orphan*/  sc_line; } ;
struct ucom_softc {struct uvscom_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__) ; 
 int /*<<< orphan*/  UVSCOM_DTR ; 
 int /*<<< orphan*/  UVSCOM_LINE_CTL ; 
 int /*<<< orphan*/  uvscom_cfg_write (struct uvscom_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uvscom_cfg_set_dtr(struct ucom_softc *ucom, uint8_t onoff)
{
	struct uvscom_softc *sc = ucom->sc_parent;

	DPRINTF("onoff = %d\n", onoff);

	if (onoff)
		sc->sc_line |= UVSCOM_DTR;
	else
		sc->sc_line &= ~UVSCOM_DTR;

	uvscom_cfg_write(sc, UVSCOM_LINE_CTL, sc->sc_line);
}