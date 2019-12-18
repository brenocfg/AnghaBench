#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  scalar_t__ u_char ;
struct TYPE_5__ {int /*<<< orphan*/  kc_arg; int /*<<< orphan*/  (* kc_func ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ kb_callback; int /*<<< orphan*/  kb_delay1; } ;
struct adb_kbd_softc {int buffers; int* buffer; int last_press; TYPE_2__ sc_kbd; int /*<<< orphan*/  sc_cv; int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_repeater; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ADB_COMMAND_TALK ; 
 int /*<<< orphan*/  KBDIO_KEYINPUT ; 
 scalar_t__ KBD_IS_ACTIVE (TYPE_2__*) ; 
 scalar_t__ KBD_IS_BUSY (TYPE_2__*) ; 
 int /*<<< orphan*/  akbd_repeat ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adb_kbd_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devctl_notify (char*,char*,char*,int /*<<< orphan*/ *) ; 
 struct adb_kbd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_to_ticks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int 
adb_kbd_receive_packet(device_t dev, u_char status, 
    u_char command, u_char reg, int len, u_char *data)
{
	struct adb_kbd_softc *sc;

	sc = device_get_softc(dev);

	if (command != ADB_COMMAND_TALK)
		return 0;

	if (reg != 0 || len != 2)
		return (0);

	mtx_lock(&sc->sc_mutex);
		/* 0x7f is always the power button */
		if (data[0] == 0x7f) {
			devctl_notify("PMU", "Button", "pressed", NULL);
			mtx_unlock(&sc->sc_mutex);
			return (0);
		} else if (data[0] == 0xff) {
			mtx_unlock(&sc->sc_mutex);
			return (0);	/* Ignore power button release. */
		}
		if ((data[0] & 0x7f) == 57 && sc->buffers < 7) {
			/* Fake the down/up cycle for caps lock */
			sc->buffer[sc->buffers++] = data[0] & 0x7f;
			sc->buffer[sc->buffers++] = (data[0] & 0x7f) | (1 << 7);
		} else {
			sc->buffer[sc->buffers++] = data[0];
		}
		if (sc->buffer[sc->buffers-1] < 0xff)
			sc->last_press = sc->buffer[sc->buffers-1];

		if ((data[1] & 0x7f) == 57 && sc->buffers < 7) {
			/* Fake the down/up cycle for caps lock */
			sc->buffer[sc->buffers++] = data[1] & 0x7f;
			sc->buffer[sc->buffers++] = (data[1] & 0x7f) | (1 << 7);
		} else {
			sc->buffer[sc->buffers++] = data[1];
		}

		if (sc->buffer[sc->buffers-1] < 0xff)
			sc->last_press = sc->buffer[sc->buffers-1];

		/* Stop any existing key repeating */
		callout_stop(&sc->sc_repeater);

		/* Schedule a repeat callback on keydown */
		if (!(sc->last_press & (1 << 7))) {
			callout_reset(&sc->sc_repeater, 
			    ms_to_ticks(sc->sc_kbd.kb_delay1), akbd_repeat, sc);
		}
	mtx_unlock(&sc->sc_mutex);

	cv_broadcast(&sc->sc_cv);

	if (KBD_IS_ACTIVE(&sc->sc_kbd) && KBD_IS_BUSY(&sc->sc_kbd)) {
		sc->sc_kbd.kb_callback.kc_func(&sc->sc_kbd,
			 KBDIO_KEYINPUT, sc->sc_kbd.kb_callback.kc_arg);
	}

	return (0);
}