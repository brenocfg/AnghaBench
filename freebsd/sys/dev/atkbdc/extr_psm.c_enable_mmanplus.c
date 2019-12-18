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
struct TYPE_2__ {int hwid; } ;
struct psm_softc {TYPE_1__ hw; int /*<<< orphan*/  kbdc; } ;
typedef  enum probearg { ____Placeholder_probearg } probearg ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  MOUSE_PS2PLUS_CHECKBITS (int*) ; 
 scalar_t__ MOUSE_PS2PLUS_PACKET_TYPE (int*) ; 
 int MOUSE_PS2PLUS_SYNC ; 
 int MOUSE_PS2PLUS_SYNCMASK ; 
 int PROBE ; 
 int TRUE ; 
 int get_mouse_status (int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  mouse_ext_command (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_mouse_scaling (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
enable_mmanplus(struct psm_softc *sc, enum probearg arg)
{
	KBDC kbdc = sc->kbdc;
	int data[3];

	/* the special sequence to enable the fourth button and the roller. */
	/*
	 * NOTE: for ScrollPoint to respond correctly, the SET_RESOLUTION
	 * must be called exactly three times since the last RESET command
	 * before this sequence. XXX
	 */
	if (!set_mouse_scaling(kbdc, 1))
		return (FALSE);
	if (!mouse_ext_command(kbdc, 0x39) || !mouse_ext_command(kbdc, 0xdb))
		return (FALSE);
	if (get_mouse_status(kbdc, data, 1, 3) < 3)
		return (FALSE);

	/*
	 * PS2++ protocol, packet type 0
	 *
	 *          b7 b6 b5 b4 b3 b2 b1 b0
	 * byte 1:  *  1  p3 p2 1  *  *  *
	 * byte 2:  1  1  p1 p0 m1 m0 1  0
	 * byte 3:  m7 m6 m5 m4 m3 m2 m1 m0
	 *
	 * p3-p0: packet type: 0
	 * m7-m0: model ID: MouseMan+:0x50,
	 *		    FirstMouse+:0x51,
	 *		    ScrollPoint:0x58...
	 */
	/* check constant bits */
	if ((data[0] & MOUSE_PS2PLUS_SYNCMASK) != MOUSE_PS2PLUS_SYNC)
		return (FALSE);
	if ((data[1] & 0xc3) != 0xc2)
		return (FALSE);
	/* check d3-d0 in byte 2 */
	if (!MOUSE_PS2PLUS_CHECKBITS(data))
		return (FALSE);
	/* check p3-p0 */
	if (MOUSE_PS2PLUS_PACKET_TYPE(data) != 0)
		return (FALSE);

	if (arg == PROBE) {
		sc->hw.hwid &= 0x00ff;
		sc->hw.hwid |= data[2] << 8;	/* save model ID */
	}

	/*
	 * MouseMan+ (or FirstMouse+) is now in its native mode, in which
	 * the wheel and the fourth button events are encoded in the
	 * special data packet. The mouse may be put in the IntelliMouse mode
	 * if it is initialized by the IntelliMouse's method.
	 */
	return (TRUE);
}