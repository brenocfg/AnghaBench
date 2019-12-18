#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ buttons; } ;
struct g_mouse_softc {int sc_do_button_update; int /*<<< orphan*/  sc_button_press_callout; TYPE_1__ sc_data; } ;

/* Variables and functions */
 int USB_MS_TO_TICKS (int) ; 
 int g_mouse_button_press_interval ; 
 int /*<<< orphan*/  g_mouse_button_press_timeout ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct g_mouse_softc*) ; 

__attribute__((used)) static void
g_mouse_button_press_timeout_reset(struct g_mouse_softc *sc)
{
	int i = g_mouse_button_press_interval;

	if (i <= 0) {
		sc->sc_data.buttons = 0;
		sc->sc_do_button_update = 0;
	} else {
		sc->sc_do_button_update = 1;
	}

	if ((i <= 0) || (i > 1023))
		i = 1023;

	i = USB_MS_TO_TICKS(i);

	usb_callout_reset(&sc->sc_button_press_callout, i, 
	    &g_mouse_button_press_timeout, sc);
}