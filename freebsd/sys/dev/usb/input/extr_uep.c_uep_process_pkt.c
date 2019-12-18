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
typedef  int u_char ;
struct uep_softc {int /*<<< orphan*/  evdev; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int,int) ; 
 int /*<<< orphan*/  evdev_push_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evdev_push_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evdev_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uep_put_queue (struct uep_softc*,int*) ; 

__attribute__((used)) static void
uep_process_pkt(struct uep_softc *sc, u_char *buf)
{
	int32_t x, y;
#ifdef EVDEV_SUPPORT
	int touch;
#endif

	if ((buf[0] & 0xFE) != 0x80) {
		DPRINTF("bad input packet format 0x%.2x\n", buf[0]);
		return;
	}

	/*
	 * Packet format is 5 bytes:
	 *
	 * 1000000T
	 * 0000AAAA
	 * 0AAAAAAA
	 * 0000BBBB
	 * 0BBBBBBB
	 *
	 * T: 1=touched 0=not touched
	 * A: bits of axis A position, MSB to LSB
	 * B: bits of axis B position, MSB to LSB
	 *
	 * For the unit I have, which is CTF1020-S from CarTFT.com,
	 * A = X and B = Y. But in NetBSD uep(4) it is other way round :)
	 *
	 * The controller sends a stream of T=1 events while the
	 * panel is touched, followed by a single T=0 event.
	 *
	 */

	x = (buf[1] << 7) | buf[2];
	y = (buf[3] << 7) | buf[4];

	DPRINTFN(2, "x %u y %u\n", x, y);

#ifdef EVDEV_SUPPORT
	touch = buf[0] & (1 << 0);
	if (touch) {
		evdev_push_abs(sc->evdev, ABS_X, x);
		evdev_push_abs(sc->evdev, ABS_Y, y);
	}
	evdev_push_key(sc->evdev, BTN_TOUCH, touch);
	evdev_sync(sc->evdev);
#else
	uep_put_queue(sc, buf);
#endif
}