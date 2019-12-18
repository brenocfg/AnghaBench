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
struct usie_softc {int /*<<< orphan*/  sc_lsr; int /*<<< orphan*/  sc_msr; } ;
struct ucom_softc {struct usie_softc* sc_parent; } ;

/* Variables and functions */

__attribute__((used)) static void
usie_uc_cfg_get_status(struct ucom_softc *ucom, uint8_t *lsr, uint8_t *msr)
{
	struct usie_softc *sc = ucom->sc_parent;

	*msr = sc->sc_msr;
	*lsr = sc->sc_lsr;
}