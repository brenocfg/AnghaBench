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
struct ft5406ts_softc {int* touch_buf; int /*<<< orphan*/  sc_tick; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/  sc_evdev; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_SLOT ; 
 int /*<<< orphan*/  ABS_MT_TRACKING_ID ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  FT5406_LOCK_ASSERT (struct ft5406ts_softc*) ; 
 size_t FT5406_NUM_POINTS ; 
 int /*<<< orphan*/  FT5406_WINDOW_SIZE ; 
 int GET_NUM_POINTS (int /*<<< orphan*/ ) ; 
 int GET_TOUCH_ID (int /*<<< orphan*/ ,int) ; 
 int GET_X (int /*<<< orphan*/ ,int) ; 
 int GET_Y (int /*<<< orphan*/ ,int) ; 
 int MAX_TOUCH_ID ; 
 int NO_POINTS ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct ft5406ts_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  evdev_push_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evdev_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ft5406ts_callout(void *data)
{
	struct ft5406ts_softc *sc = (struct ft5406ts_softc *)data;
	int points;
	int id, i, x, y;

	FT5406_LOCK_ASSERT(sc);

	memcpy(sc->sc_window, sc->touch_buf, FT5406_WINDOW_SIZE);
	sc->touch_buf[FT5406_NUM_POINTS] = NO_POINTS;

	points = GET_NUM_POINTS(sc->sc_window);
	/*
	 * No update from VC - do nothing.
	 */
	if (points == NO_POINTS)
		goto out;

	for (i = 0; i < points; i++) {
		id = GET_TOUCH_ID(sc->sc_window, i);
		x = GET_X(sc->sc_window, i);
		y = GET_Y(sc->sc_window, i);

		if (id > MAX_TOUCH_ID) {
			device_printf(sc->sc_dev, "bad touch id: %d", id);
			continue;
		}
		evdev_push_event(sc->sc_evdev, EV_ABS, ABS_MT_SLOT, id);
		evdev_push_event(sc->sc_evdev, EV_ABS, ABS_MT_TRACKING_ID, id);
		evdev_push_event(sc->sc_evdev, EV_ABS, ABS_MT_POSITION_X, x);
		evdev_push_event(sc->sc_evdev, EV_ABS, ABS_MT_POSITION_Y, y);
	}
	evdev_sync(sc->sc_evdev);
out:
	callout_reset(&sc->sc_callout, sc->sc_tick, ft5406ts_callout, sc);
}