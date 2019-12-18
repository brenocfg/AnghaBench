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
struct uaudio_softc {int /*<<< orphan*/ * sc_mixer_lock; int /*<<< orphan*/  sc_mixer_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int) ; 

int
uaudio_mixer_uninit_sub(struct uaudio_softc *sc)
{
	DPRINTF("\n");

	usbd_transfer_unsetup(sc->sc_mixer_xfer, 1);

	sc->sc_mixer_lock = NULL;

	return (0);
}