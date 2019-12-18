#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pal_buf; int /*<<< orphan*/  adp; int /*<<< orphan*/ * state_buf; } ;
typedef  TYPE_1__ vga_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ bootverbose ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vidd_save_palette (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vidd_save_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
vga_suspend(device_t dev)
{
	vga_softc_t *sc;
	int nbytes;

	sc = device_get_softc(dev);

	/* Save the video state across the suspend. */
	if (sc->state_buf != NULL)
		goto save_palette;
	nbytes = vidd_save_state(sc->adp, NULL, 0);
	if (nbytes <= 0)
		goto save_palette;
	sc->state_buf = malloc(nbytes, M_TEMP, M_NOWAIT);
	if (sc->state_buf == NULL)
		goto save_palette;
	if (bootverbose)
		device_printf(dev, "saving %d bytes of video state\n", nbytes);
	if (vidd_save_state(sc->adp, sc->state_buf, nbytes) != 0) {
		device_printf(dev, "failed to save state (nbytes=%d)\n",
		    nbytes);
		free(sc->state_buf, M_TEMP);
		sc->state_buf = NULL;
	}

save_palette:
	/* Save the color palette across the suspend. */
	if (sc->pal_buf != NULL)
		return;
	sc->pal_buf = malloc(256 * 3, M_TEMP, M_NOWAIT);
	if (sc->pal_buf == NULL)
		return;
	if (bootverbose)
		device_printf(dev, "saving color palette\n");
	if (vidd_save_palette(sc->adp, sc->pal_buf) != 0) {
		device_printf(dev, "failed to save palette\n");
		free(sc->pal_buf, M_TEMP);
		sc->pal_buf = NULL;
	}
}