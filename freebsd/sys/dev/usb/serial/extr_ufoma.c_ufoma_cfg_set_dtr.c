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
struct ufoma_softc {int /*<<< orphan*/  sc_line; scalar_t__ sc_nobulk; } ;
struct ucom_softc {struct ufoma_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCDC_LINE_DTR ; 
 int /*<<< orphan*/  ufoma_cfg_set_line_state (struct ufoma_softc*) ; 

__attribute__((used)) static void
ufoma_cfg_set_dtr(struct ucom_softc *ucom, uint8_t onoff)
{
	struct ufoma_softc *sc = ucom->sc_parent;

	if (sc->sc_nobulk) {
		return;
	}
	if (onoff)
		sc->sc_line |= UCDC_LINE_DTR;
	else
		sc->sc_line &= ~UCDC_LINE_DTR;

	ufoma_cfg_set_line_state(sc);
}