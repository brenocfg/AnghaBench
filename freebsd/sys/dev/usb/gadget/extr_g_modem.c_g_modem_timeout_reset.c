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
struct g_modem_softc {int sc_tx_interval; int /*<<< orphan*/  sc_callout; } ;

/* Variables and functions */
 int USB_MS_TO_TICKS (int) ; 
 int g_modem_pattern_interval ; 
 int /*<<< orphan*/  g_modem_timeout ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct g_modem_softc*) ; 

__attribute__((used)) static void
g_modem_timeout_reset(struct g_modem_softc *sc)
{
	int i = g_modem_pattern_interval;

	sc->sc_tx_interval = i;

	if (i <= 0)
		i = 1;
	else if (i > 1023)
		i = 1023;

	i = USB_MS_TO_TICKS(i);

	usb_callout_reset(&sc->sc_callout, i, &g_modem_timeout, sc);
}