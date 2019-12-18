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
struct cbb_softc {int flags; int /*<<< orphan*/  cbdev; int /*<<< orphan*/ * exca; scalar_t__ cardok; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DETACH_CARD (int /*<<< orphan*/ ) ; 
 int CBB_16BIT_CARD ; 
 int /*<<< orphan*/  cbb_destroy_res (struct cbb_softc*) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_removal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cbb_removal(struct cbb_softc *sc)
{
	sc->cardok = 0;
	if (sc->flags & CBB_16BIT_CARD) {
		exca_removal(&sc->exca[0]);
	} else {
		if (device_is_attached(sc->cbdev))
			CARD_DETACH_CARD(sc->cbdev);
	}
	cbb_destroy_res(sc);
}