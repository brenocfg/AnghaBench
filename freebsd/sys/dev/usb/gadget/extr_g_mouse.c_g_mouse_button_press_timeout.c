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
struct g_mouse_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ) ; 
 size_t G_MOUSE_INTR_DT ; 
 int /*<<< orphan*/  g_mouse_button_press_timeout_reset (struct g_mouse_softc*) ; 
 int /*<<< orphan*/  g_mouse_update_mode_radius (struct g_mouse_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_mouse_button_press_timeout(void *arg)
{
	struct g_mouse_softc *sc = arg;

	g_mouse_update_mode_radius(sc);

	DPRINTFN(11, "Timeout %p (button press)\n", sc->sc_xfer[G_MOUSE_INTR_DT]);

	g_mouse_button_press_timeout_reset(sc);

	usbd_transfer_start(sc->sc_xfer[G_MOUSE_INTR_DT]);
}