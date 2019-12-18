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
struct psm_softc {int flags; int xold; int yold; } ;
struct TYPE_5__ {int* ipacket; } ;
typedef  TYPE_1__ packetbuf_t ;
struct TYPE_6__ {int button; } ;
typedef  TYPE_2__ mousestatus_t ;

/* Variables and functions */
#define  MOUSE_BUTTON1DOWN 129 
#define  MOUSE_BUTTON3DOWN 128 
 int MOUSE_BUTTON4DOWN ; 
 int MOUSE_PS2VERSA_BUTTONS ; 
 int MOUSE_PS2VERSA_IN_USE ; 
 int MOUSE_PS2VERSA_TAP ; 
 int PSM_FLAGS_FINGERDOWN ; 

__attribute__((used)) static void
proc_versapad(struct psm_softc *sc, packetbuf_t *pb, mousestatus_t *ms,
    int *x, int *y, int *z)
{
	static int butmap_versapad[8] = {
		0,
		MOUSE_BUTTON3DOWN,
		0,
		MOUSE_BUTTON3DOWN,
		MOUSE_BUTTON1DOWN,
		MOUSE_BUTTON1DOWN | MOUSE_BUTTON3DOWN,
		MOUSE_BUTTON1DOWN,
		MOUSE_BUTTON1DOWN | MOUSE_BUTTON3DOWN
	};
	int c, x0, y0;

	/* VersaPad PS/2 absolute mode message format
	 *
	 * [packet1]     7   6   5   4   3   2   1   0(LSB)
	 *  ipacket[0]:  1   1   0   A   1   L   T   R
	 *  ipacket[1]: H7  H6  H5  H4  H3  H2  H1  H0
	 *  ipacket[2]: V7  V6  V5  V4  V3  V2  V1  V0
	 *  ipacket[3]:  1   1   1   A   1   L   T   R
	 *  ipacket[4]:V11 V10  V9  V8 H11 H10  H9  H8
	 *  ipacket[5]:  0  P6  P5  P4  P3  P2  P1  P0
	 *
	 * [note]
	 *  R: right physical mouse button (1=on)
	 *  T: touch pad virtual button (1=tapping)
	 *  L: left physical mouse button (1=on)
	 *  A: position data is valid (1=valid)
	 *  H: horizontal data (12bit signed integer. H11 is sign bit.)
	 *  V: vertical data (12bit signed integer. V11 is sign bit.)
	 *  P: pressure data
	 *
	 * Tapping is mapped to MOUSE_BUTTON4.
	 */
	c = pb->ipacket[0];
	*x = *y = 0;
	ms->button = butmap_versapad[c & MOUSE_PS2VERSA_BUTTONS];
	ms->button |= (c & MOUSE_PS2VERSA_TAP) ? MOUSE_BUTTON4DOWN : 0;
	if (c & MOUSE_PS2VERSA_IN_USE) {
		x0 = pb->ipacket[1] | (((pb->ipacket[4]) & 0x0f) << 8);
		y0 = pb->ipacket[2] | (((pb->ipacket[4]) & 0xf0) << 4);
		if (x0 & 0x800)
			x0 -= 0x1000;
		if (y0 & 0x800)
			y0 -= 0x1000;
		if (sc->flags & PSM_FLAGS_FINGERDOWN) {
			*x = sc->xold - x0;
			*y = y0 - sc->yold;
			if (*x < 0)	/* XXX */
				++*x;
			else if (*x)
				--*x;
			if (*y < 0)
				++*y;
			else if (*y)
				--*y;
		} else
			sc->flags |= PSM_FLAGS_FINGERDOWN;
		sc->xold = x0;
		sc->yold = y0;
	} else
		sc->flags &= ~PSM_FLAGS_FINGERDOWN;
}