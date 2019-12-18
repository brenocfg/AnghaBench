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
struct ucom_softc {size_t sc_subunit; struct u3g_softc* sc_parent; } ;
struct u3g_softc {int /*<<< orphan*/ * sc_msr; int /*<<< orphan*/ * sc_lsr; } ;

/* Variables and functions */

__attribute__((used)) static void
u3g_cfg_get_status(struct ucom_softc *ucom, uint8_t *lsr, uint8_t *msr)
{
	struct u3g_softc *sc = ucom->sc_parent;

	/* XXX Note: sc_lsr is always zero */
	*lsr = sc->sc_lsr[ucom->sc_subunit];
	*msr = sc->sc_msr[ucom->sc_subunit];
}