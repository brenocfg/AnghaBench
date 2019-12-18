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
typedef  int /*<<< orphan*/  uint8_t ;
struct ucom_softc {struct uchcom_softc* sc_parent; } ;
struct uchcom_softc {int /*<<< orphan*/  sc_rts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uchcom_set_dtr_rts (struct uchcom_softc*) ; 

__attribute__((used)) static void
uchcom_cfg_set_rts(struct ucom_softc *ucom, uint8_t onoff)
{
	struct uchcom_softc *sc = ucom->sc_parent;

	DPRINTF("onoff = %d\n", onoff);

	sc->sc_rts = onoff;
	uchcom_set_dtr_rts(sc);
}