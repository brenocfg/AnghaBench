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
typedef  int /*<<< orphan*/  u_int ;
typedef  scalar_t__ u_char ;
struct TYPE_2__ {int buttons; } ;
struct adb_mouse_softc {int flags; int sc_tapping; int button_buf; int xdelta; int ydelta; int buttons; int /*<<< orphan*/  rsel; int /*<<< orphan*/  sc_cv; int /*<<< orphan*/  sc_mtx; TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ADB_COMMAND_TALK ; 
 int AMS_EXTENDED ; 
 int AMS_TOUCHPAD ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 struct adb_mouse_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rounddown2 (int,int) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int 
adb_mouse_receive_packet(device_t dev, u_char status, u_char command, 
    u_char reg, int len, u_char *data) 
{
	struct adb_mouse_softc *sc;
	int i = 0;
	int xdelta, ydelta;
	int buttons, tmp_buttons;

	sc = device_get_softc(dev);

	if (command != ADB_COMMAND_TALK || reg != 0 || len < 2)
		return (0);

	ydelta = data[0] & 0x7f;
	xdelta = data[1] & 0x7f;

	buttons = 0;
	buttons |= !(data[0] & 0x80);
	buttons |= !(data[1] & 0x80) << 1;

	if (sc->flags & AMS_EXTENDED) {
		for (i = 2; i < len && i < 5; i++) {
			xdelta |= (data[i] & 0x07) << (3*i + 1);
			ydelta |= (data[i] & 0x70) << (3*i - 3);

			buttons |= !(data[i] & 0x08) << (2*i - 2);
			buttons |= !(data[i] & 0x80) << (2*i - 1);
		}
	} else {
		len = 2; /* Ignore extra data */
	}

	/* Do sign extension as necessary */
	if (xdelta & (0x40 << 3*(len-2)))
		xdelta |= 0xffffffc0 << 3*(len - 2);
	if (ydelta & (0x40 << 3*(len-2)))
		ydelta |= 0xffffffc0 << 3*(len - 2);

	if ((sc->flags & AMS_TOUCHPAD) && (sc->sc_tapping == 1)) {
		tmp_buttons = buttons;
		if (buttons == 0x12) {
			/* Map a double tap on button 3.
			   Keep the button state for the next sequence.
			   A double tap sequence is followed by a single tap
			   sequence.
			*/
			tmp_buttons = 0x3;
			sc->button_buf = tmp_buttons;
		} else if (buttons == 0x2) {
			/* Map a single tap on button 2. But only if it is
			   not a successor from a double tap.
			*/
			if (sc->button_buf != 0x3) 
				tmp_buttons = 0x2;
			else
				tmp_buttons = 0;

			sc->button_buf = 0;
		}
		buttons = tmp_buttons;
	}

	/*
	 * Some mice report high-numbered buttons on the wrong button number,
	 * so set the highest-numbered real button as pressed if there are
	 * mysterious high-numbered ones set.
	 *
	 * Don't do this for touchpads, because touchpads also trigger
	 * high button events when they are touched.
	 */

	if (rounddown2(buttons, 1 << sc->hw.buttons)
	    && !(sc->flags & AMS_TOUCHPAD)) {
		buttons |= 1 << (sc->hw.buttons - 1);
	}
	buttons &= (1 << sc->hw.buttons) - 1;

	mtx_lock(&sc->sc_mtx);

	/* Add in our new deltas, and take into account
	   Apple's opposite meaning for Y axis motion */

	sc->xdelta += xdelta;
	sc->ydelta -= ydelta;

	sc->buttons = buttons;

	mtx_unlock(&sc->sc_mtx);

	cv_broadcast(&sc->sc_cv);
	selwakeuppri(&sc->rsel, PZERO);

	return (0);
}