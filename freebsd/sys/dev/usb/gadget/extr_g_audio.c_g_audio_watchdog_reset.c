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
struct g_audio_softc {int /*<<< orphan*/  sc_watchdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_audio_watchdog ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct g_audio_softc*) ; 

__attribute__((used)) static void
g_audio_watchdog_reset(struct g_audio_softc *sc)
{
	usb_callout_reset(&sc->sc_watchdog, hz, &g_audio_watchdog, sc);
}