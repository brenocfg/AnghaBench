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
struct psm_softc {int dummy; } ;
struct TYPE_5__ {int* ipacket; } ;
typedef  TYPE_1__ packetbuf_t ;
struct TYPE_6__ {int button; int obutton; } ;
typedef  TYPE_2__ mousestatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int MOUSE_BUTTON4DOWN ; 
 int MOUSE_BUTTON5DOWN ; 
 int MOUSE_EXTBUTTONS ; 
 int MOUSE_PS2PLUS_BUTTON4DOWN ; 
 int MOUSE_PS2PLUS_BUTTON5DOWN ; 
 scalar_t__ MOUSE_PS2PLUS_CHECKBITS (int*) ; 
 int MOUSE_PS2PLUS_PACKET_TYPE (int*) ; 
 int MOUSE_PS2PLUS_SYNC ; 
 int MOUSE_PS2PLUS_SYNCMASK ; 
 int MOUSE_PS2PLUS_ZNEG ; 
 int MOUSE_SPOINT_WNEG ; 
 int MOUSE_SPOINT_ZNEG ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int abs (int) ; 

__attribute__((used)) static void
proc_mmanplus(struct psm_softc *sc, packetbuf_t *pb, mousestatus_t *ms,
    int *x, int *y, int *z)
{

	/*
	 * PS2++ protocol packet
	 *
	 *          b7 b6 b5 b4 b3 b2 b1 b0
	 * byte 1:  *  1  p3 p2 1  *  *  *
	 * byte 2:  c1 c2 p1 p0 d1 d0 1  0
	 *
	 * p3-p0: packet type
	 * c1, c2: c1 & c2 == 1, if p2 == 0
	 *         c1 & c2 == 0, if p2 == 1
	 *
	 * packet type: 0 (device type)
	 * See comments in enable_mmanplus() below.
	 *
	 * packet type: 1 (wheel data)
	 *
	 *          b7 b6 b5 b4 b3 b2 b1 b0
	 * byte 3:  h  *  B5 B4 s  d2 d1 d0
	 *
	 * h: 1, if horizontal roller data
	 *    0, if vertical roller data
	 * B4, B5: button 4 and 5
	 * s: sign bit
	 * d2-d0: roller data
	 *
	 * packet type: 2 (reserved)
	 */
	if (((pb->ipacket[0] & MOUSE_PS2PLUS_SYNCMASK) == MOUSE_PS2PLUS_SYNC) &&
	    (abs(*x) > 191) && MOUSE_PS2PLUS_CHECKBITS(pb->ipacket)) {
		/*
		 * the extended data packet encodes button
		 * and wheel events
		 */
		switch (MOUSE_PS2PLUS_PACKET_TYPE(pb->ipacket)) {
		case 1:
			/* wheel data packet */
			*x = *y = 0;
			if (pb->ipacket[2] & 0x80) {
				/* XXX horizontal roller count - ignore it */
				;
			} else {
				/* vertical roller count */
				*z = (pb->ipacket[2] & MOUSE_PS2PLUS_ZNEG) ?
				    (pb->ipacket[2] & 0x0f) - 16 :
				    (pb->ipacket[2] & 0x0f);
			}
			ms->button |= (pb->ipacket[2] &
			    MOUSE_PS2PLUS_BUTTON4DOWN) ?
			    MOUSE_BUTTON4DOWN : 0;
			ms->button |= (pb->ipacket[2] &
			    MOUSE_PS2PLUS_BUTTON5DOWN) ?
			    MOUSE_BUTTON5DOWN : 0;
			break;
		case 2:
			/*
			 * this packet type is reserved by
			 * Logitech...
			 */
			/*
			 * IBM ScrollPoint Mouse uses this
			 * packet type to encode both vertical
			 * and horizontal scroll movement.
			 */
			*x = *y = 0;
			/* horizontal count */
			if (pb->ipacket[2] & 0x0f)
				*z = (pb->ipacket[2] & MOUSE_SPOINT_WNEG) ?
				    -2 : 2;
			/* vertical count */
			if (pb->ipacket[2] & 0xf0)
				*z = (pb->ipacket[2] & MOUSE_SPOINT_ZNEG) ?
				    -1 : 1;
			break;
		case 0:
			/* device type packet - shouldn't happen */
			/* FALLTHROUGH */
		default:
			*x = *y = 0;
			ms->button = ms->obutton;
			VLOG(1, (LOG_DEBUG, "psmintr: unknown PS2++ packet "
			    "type %d: 0x%02x 0x%02x 0x%02x\n",
			    MOUSE_PS2PLUS_PACKET_TYPE(pb->ipacket),
			    pb->ipacket[0], pb->ipacket[1], pb->ipacket[2]));
			break;
		}
	} else {
		/* preserve button states */
		ms->button |= ms->obutton & MOUSE_EXTBUTTONS;
	}
}