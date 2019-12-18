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
struct ft5406ts_softc {int /*<<< orphan*/  sc_tick; int /*<<< orphan*/  sc_callout; } ;
struct evdev_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FT5406_LOCK_ASSERT (struct ft5406ts_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ft5406ts_softc*) ; 
 struct ft5406ts_softc* evdev_get_softc (struct evdev_dev*) ; 
 int /*<<< orphan*/  ft5406ts_callout ; 

__attribute__((used)) static int
ft5406ts_ev_open(struct evdev_dev *evdev)
{
	struct ft5406ts_softc *sc = evdev_get_softc(evdev);

	FT5406_LOCK_ASSERT(sc);

	callout_reset(&sc->sc_callout, sc->sc_tick, ft5406ts_callout, sc);

	return (0);
}