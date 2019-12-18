#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int count; int tail; int /*<<< orphan*/ * buf; } ;
struct TYPE_20__ {int flags; int dx; int dy; int dz; int button; } ;
struct TYPE_22__ {int* ipacket; int inputbytes; } ;
struct TYPE_19__ {scalar_t__ level; int accelfactor; } ;
struct TYPE_18__ {int model; } ;
struct psm_softc {size_t pqueue_start; size_t pqueue_end; int button; int config; int state; int /*<<< orphan*/  idletimeout; int /*<<< orphan*/  softcallout; int /*<<< orphan*/ * async; int /*<<< orphan*/  rsel; TYPE_4__ queue; int /*<<< orphan*/  watchdog; TYPE_3__ status; TYPE_5__ idlepacket; TYPE_2__ mode; int /*<<< orphan*/  evdev_r; TYPE_1__ hw; TYPE_5__* pqueue; int /*<<< orphan*/  lastsoftintr; } ;
typedef  TYPE_5__ packetbuf_t ;
struct TYPE_23__ {int obutton; int button; int dx; int dy; int dz; int flags; } ;
typedef  TYPE_6__ mousestatus_t ;

/* Variables and functions */
 int EVDEV_RCPT_HW_MOUSE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int MOUSE_4DPLUS_BUTTON4DOWN ; 
 int MOUSE_4DPLUS_ZNEG ; 
 int MOUSE_4D_WHEELBITS ; 
#define  MOUSE_BUTTON1DOWN 144 
#define  MOUSE_BUTTON2DOWN 143 
#define  MOUSE_BUTTON3DOWN 142 
 int MOUSE_BUTTON4DOWN ; 
 int MOUSE_BUTTON5DOWN ; 
 int MOUSE_EXPLORER_BUTTON4DOWN ; 
 int MOUSE_EXPLORER_BUTTON5DOWN ; 
 int MOUSE_EXPLORER_ZNEG ; 
 int MOUSE_EXTBUTTONS ; 
#define  MOUSE_MODEL_4D 141 
#define  MOUSE_MODEL_4DPLUS 140 
#define  MOUSE_MODEL_ELANTECH 139 
#define  MOUSE_MODEL_EXPLORER 138 
#define  MOUSE_MODEL_GENERIC 137 
#define  MOUSE_MODEL_GLIDEPOINT 136 
#define  MOUSE_MODEL_INTELLI 135 
#define  MOUSE_MODEL_MOUSEMANPLUS 134 
#define  MOUSE_MODEL_NET 133 
#define  MOUSE_MODEL_NETSCROLL 132 
#define  MOUSE_MODEL_SYNAPTICS 131 
#define  MOUSE_MODEL_THINK 130 
#define  MOUSE_MODEL_TRACKPOINT 129 
#define  MOUSE_MODEL_VERSAPAD 128 
 int MOUSE_POSCHANGED ; 
 int MOUSE_PS2INTELLI_BUTTON4DOWN ; 
 int MOUSE_PS2INTELLI_BUTTON5DOWN ; 
 int MOUSE_PS2_BUTTON1DOWN ; 
 int MOUSE_PS2_BUTTON3DOWN ; 
 int MOUSE_PS2_BUTTONS ; 
 int MOUSE_PS2_PACKETSIZE ; 
 int MOUSE_PS2_TAP ; 
 int MOUSE_PS2_XNEG ; 
 int MOUSE_PS2_XOVERFLOW ; 
 int MOUSE_PS2_YNEG ; 
 int PSM_ASLP ; 
 int PSM_CONFIG_FORCETAP ; 
 scalar_t__ PSM_LEVEL_NATIVE ; 
 size_t PSM_PACKETQUEUE ; 
 int PSM_SOFTARMED ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct psm_softc*) ; 
 int /*<<< orphan*/  evdev_push_mouse_btn (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evdev_push_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int evdev_rcpt_mask ; 
 int /*<<< orphan*/  evdev_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmicrouptime (int /*<<< orphan*/ *) ; 
 int imin (int,int) ; 
 int /*<<< orphan*/  pgsigio (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_elantech (struct psm_softc*,TYPE_5__*,TYPE_6__*,int*,int*,int*) ; 
 int /*<<< orphan*/  proc_mmanplus (struct psm_softc*,TYPE_5__*,TYPE_6__*,int*,int*,int*) ; 
 int /*<<< orphan*/  proc_synaptics (struct psm_softc*,TYPE_5__*,TYPE_6__*,int*,int*,int*) ; 
 int /*<<< orphan*/  proc_synaptics_mux (struct psm_softc*,TYPE_5__*) ; 
 int /*<<< orphan*/  proc_versapad (struct psm_softc*,TYPE_5__*,TYPE_6__*,int*,int*,int*) ; 
 int /*<<< orphan*/  psmsoftintridle ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int tame_mouse (struct psm_softc*,TYPE_5__*,TYPE_6__*,int*) ; 
 int /*<<< orphan*/  timevalclear (int /*<<< orphan*/ *) ; 
 scalar_t__ timevalisset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvtohz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct psm_softc*) ; 

__attribute__((used)) static void
psmsoftintr(void *arg)
{
	/*
	 * the table to turn PS/2 mouse button bits (MOUSE_PS2_BUTTON?DOWN)
	 * into `mousestatus' button bits (MOUSE_BUTTON?DOWN).
	 */
	static int butmap[8] = {
		0,
		MOUSE_BUTTON1DOWN,
		MOUSE_BUTTON3DOWN,
		MOUSE_BUTTON1DOWN | MOUSE_BUTTON3DOWN,
		MOUSE_BUTTON2DOWN,
		MOUSE_BUTTON1DOWN | MOUSE_BUTTON2DOWN,
		MOUSE_BUTTON2DOWN | MOUSE_BUTTON3DOWN,
		MOUSE_BUTTON1DOWN | MOUSE_BUTTON2DOWN | MOUSE_BUTTON3DOWN
	};
	struct psm_softc *sc = arg;
	mousestatus_t ms;
	packetbuf_t *pb;
	int x, y, z, c, l, s;

	getmicrouptime(&sc->lastsoftintr);

	s = spltty();

	do {
		pb = &sc->pqueue[sc->pqueue_start];

		if (sc->mode.level == PSM_LEVEL_NATIVE)
			goto next_native;

		c = pb->ipacket[0];
		/*
		 * A kludge for Kensington device!
		 * The MSB of the horizontal count appears to be stored in
		 * a strange place.
		 */
		if (sc->hw.model == MOUSE_MODEL_THINK)
			pb->ipacket[1] |= (c & MOUSE_PS2_XOVERFLOW) ? 0x80 : 0;

		/* ignore the overflow bits... */
		x = (c & MOUSE_PS2_XNEG) ?
		    pb->ipacket[1] - 256 : pb->ipacket[1];
		y = (c & MOUSE_PS2_YNEG) ?
		    pb->ipacket[2] - 256 : pb->ipacket[2];
		z = 0;
		ms.obutton = sc->button;	  /* previous button state */
		ms.button = butmap[c & MOUSE_PS2_BUTTONS];
		/* `tapping' action */
		if (sc->config & PSM_CONFIG_FORCETAP)
			ms.button |= ((c & MOUSE_PS2_TAP)) ?
			    0 : MOUSE_BUTTON4DOWN;
		timevalclear(&sc->idletimeout);
		sc->idlepacket.inputbytes = 0;

		switch (sc->hw.model) {

		case MOUSE_MODEL_EXPLORER:
			/*
			 *          b7 b6 b5 b4 b3 b2 b1 b0
			 * byte 1:  oy ox sy sx 1  M  R  L
			 * byte 2:  x  x  x  x  x  x  x  x
			 * byte 3:  y  y  y  y  y  y  y  y
			 * byte 4:  *  *  S2 S1 s  d2 d1 d0
			 *
			 * L, M, R, S1, S2: left, middle, right and side buttons
			 * s: wheel data sign bit
			 * d2-d0: wheel data
			 */
			z = (pb->ipacket[3] & MOUSE_EXPLORER_ZNEG) ?
			    (pb->ipacket[3] & 0x0f) - 16 :
			    (pb->ipacket[3] & 0x0f);
			ms.button |=
			    (pb->ipacket[3] & MOUSE_EXPLORER_BUTTON4DOWN) ?
			    MOUSE_BUTTON4DOWN : 0;
			ms.button |=
			    (pb->ipacket[3] & MOUSE_EXPLORER_BUTTON5DOWN) ?
			    MOUSE_BUTTON5DOWN : 0;
			break;

		case MOUSE_MODEL_INTELLI:
		case MOUSE_MODEL_NET:
			/* wheel data is in the fourth byte */
			z = (char)pb->ipacket[3];
			/*
			 * XXX some mice may send 7 when there is no Z movement?			 */
			if ((z >= 7) || (z <= -7))
				z = 0;
			/* some compatible mice have additional buttons */
			ms.button |= (c & MOUSE_PS2INTELLI_BUTTON4DOWN) ?
			    MOUSE_BUTTON4DOWN : 0;
			ms.button |= (c & MOUSE_PS2INTELLI_BUTTON5DOWN) ?
			    MOUSE_BUTTON5DOWN : 0;
			break;

		case MOUSE_MODEL_MOUSEMANPLUS:
			proc_mmanplus(sc, pb, &ms, &x, &y, &z);
			break;

		case MOUSE_MODEL_GLIDEPOINT:
			/* `tapping' action */
			ms.button |= ((c & MOUSE_PS2_TAP)) ? 0 :
			    MOUSE_BUTTON4DOWN;
			break;

		case MOUSE_MODEL_NETSCROLL:
			/*
			 * three additional bytes encode buttons and
			 * wheel events
			 */
			ms.button |= (pb->ipacket[3] & MOUSE_PS2_BUTTON3DOWN) ?
			    MOUSE_BUTTON4DOWN : 0;
			ms.button |= (pb->ipacket[3] & MOUSE_PS2_BUTTON1DOWN) ?
			    MOUSE_BUTTON5DOWN : 0;
			z = (pb->ipacket[3] & MOUSE_PS2_XNEG) ?
			    pb->ipacket[4] - 256 : pb->ipacket[4];
			break;

		case MOUSE_MODEL_THINK:
			/* the fourth button state in the first byte */
			ms.button |= (c & MOUSE_PS2_TAP) ?
			    MOUSE_BUTTON4DOWN : 0;
			break;

		case MOUSE_MODEL_VERSAPAD:
			proc_versapad(sc, pb, &ms, &x, &y, &z);
			c = ((x < 0) ? MOUSE_PS2_XNEG : 0) |
			    ((y < 0) ? MOUSE_PS2_YNEG : 0);
			break;

		case MOUSE_MODEL_4D:
			/*
			 *          b7 b6 b5 b4 b3 b2 b1 b0
			 * byte 1:  s2 d2 s1 d1 1  M  R  L
			 * byte 2:  sx x  x  x  x  x  x  x
			 * byte 3:  sy y  y  y  y  y  y  y
			 *
			 * s1: wheel 1 direction
			 * d1: wheel 1 data
			 * s2: wheel 2 direction
			 * d2: wheel 2 data
			 */
			x = (pb->ipacket[1] & 0x80) ?
			    pb->ipacket[1] - 256 : pb->ipacket[1];
			y = (pb->ipacket[2] & 0x80) ?
			    pb->ipacket[2] - 256 : pb->ipacket[2];
			switch (c & MOUSE_4D_WHEELBITS) {
			case 0x10:
				z = 1;
				break;
			case 0x30:
				z = -1;
				break;
			case 0x40:	/* XXX 2nd wheel turning right */
				z = 2;
				break;
			case 0xc0:	/* XXX 2nd wheel turning left */
				z = -2;
				break;
			}
			break;

		case MOUSE_MODEL_4DPLUS:
			if ((x < 16 - 256) && (y < 16 - 256)) {
				/*
				 *          b7 b6 b5 b4 b3 b2 b1 b0
				 * byte 1:  0  0  1  1  1  M  R  L
				 * byte 2:  0  0  0  0  1  0  0  0
				 * byte 3:  0  0  0  0  S  s  d1 d0
				 *
				 * L, M, R, S: left, middle, right,
				 *             and side buttons
				 * s: wheel data sign bit
				 * d1-d0: wheel data
				 */
				x = y = 0;
				if (pb->ipacket[2] & MOUSE_4DPLUS_BUTTON4DOWN)
					ms.button |= MOUSE_BUTTON4DOWN;
				z = (pb->ipacket[2] & MOUSE_4DPLUS_ZNEG) ?
				    ((pb->ipacket[2] & 0x07) - 8) :
				    (pb->ipacket[2] & 0x07) ;
			} else {
				/* preserve previous button states */
				ms.button |= ms.obutton & MOUSE_EXTBUTTONS;
			}
			break;

		case MOUSE_MODEL_SYNAPTICS:
			if (pb->inputbytes == MOUSE_PS2_PACKETSIZE)
				if (proc_synaptics_mux(sc, pb))
					goto next;

			if (proc_synaptics(sc, pb, &ms, &x, &y, &z) != 0) {
				VLOG(3, (LOG_DEBUG, "synaptics: "
				    "packet rejected\n"));
				goto next;
			}
			break;

		case MOUSE_MODEL_ELANTECH:
			if (proc_elantech(sc, pb, &ms, &x, &y, &z) != 0) {
				VLOG(3, (LOG_DEBUG, "elantech: "
				    "packet rejected\n"));
				goto next;
			}
			break;

		case MOUSE_MODEL_TRACKPOINT:
		case MOUSE_MODEL_GENERIC:
		default:
			break;
		}

#ifdef EVDEV_SUPPORT
	if (evdev_rcpt_mask & EVDEV_RCPT_HW_MOUSE &&
	    sc->hw.model != MOUSE_MODEL_ELANTECH &&
	    sc->hw.model != MOUSE_MODEL_SYNAPTICS) {
		evdev_push_rel(sc->evdev_r, REL_X, x);
		evdev_push_rel(sc->evdev_r, REL_Y, -y);

		switch (sc->hw.model) {
		case MOUSE_MODEL_EXPLORER:
		case MOUSE_MODEL_INTELLI:
		case MOUSE_MODEL_NET:
		case MOUSE_MODEL_NETSCROLL:
		case MOUSE_MODEL_4DPLUS:
			evdev_push_rel(sc->evdev_r, REL_WHEEL, -z);
			break;
		case MOUSE_MODEL_MOUSEMANPLUS:
		case MOUSE_MODEL_4D:
			switch (z) {
			case 1:
			case -1:
				evdev_push_rel(sc->evdev_r, REL_WHEEL, -z);
				break;
			case 2:
			case -2:
				evdev_push_rel(sc->evdev_r, REL_HWHEEL, z / 2);
				break;
			}
			break;
		}

		evdev_push_mouse_btn(sc->evdev_r, ms.button);
		evdev_sync(sc->evdev_r);
	}
#endif

	/* scale values */
	if (sc->mode.accelfactor >= 1) {
		if (x != 0) {
			x = x * x / sc->mode.accelfactor;
			if (x == 0)
				x = 1;
			if (c & MOUSE_PS2_XNEG)
				x = -x;
		}
		if (y != 0) {
			y = y * y / sc->mode.accelfactor;
			if (y == 0)
				y = 1;
			if (c & MOUSE_PS2_YNEG)
				y = -y;
		}
	}

	/* Store last packet for reinjection if it has not been set already */
	if (timevalisset(&sc->idletimeout) && sc->idlepacket.inputbytes == 0)
		sc->idlepacket = *pb;

	ms.dx = x;
	ms.dy = y;
	ms.dz = z;
	ms.flags = ((x || y || z) ? MOUSE_POSCHANGED : 0) |
	    (ms.obutton ^ ms.button);

	pb->inputbytes = tame_mouse(sc, pb, &ms, pb->ipacket);

	sc->status.flags |= ms.flags;
	sc->status.dx += ms.dx;
	sc->status.dy += ms.dy;
	sc->status.dz += ms.dz;
	sc->status.button = ms.button;
	sc->button = ms.button;

next_native:
	sc->watchdog = FALSE;

	/* queue data */
	if (sc->queue.count + pb->inputbytes < sizeof(sc->queue.buf)) {
		l = imin(pb->inputbytes,
		    sizeof(sc->queue.buf) - sc->queue.tail);
		bcopy(&pb->ipacket[0], &sc->queue.buf[sc->queue.tail], l);
		if (pb->inputbytes > l)
			bcopy(&pb->ipacket[l], &sc->queue.buf[0],
			    pb->inputbytes - l);
		sc->queue.tail = (sc->queue.tail + pb->inputbytes) %
		    sizeof(sc->queue.buf);
		sc->queue.count += pb->inputbytes;
	}

next:
	pb->inputbytes = 0;
	if (++sc->pqueue_start >= PSM_PACKETQUEUE)
		sc->pqueue_start = 0;
	} while (sc->pqueue_start != sc->pqueue_end);

	if (sc->state & PSM_ASLP) {
		sc->state &= ~PSM_ASLP;
		wakeup(sc);
	}
	selwakeuppri(&sc->rsel, PZERO);
	if (sc->async != NULL) {
		pgsigio(&sc->async, SIGIO, 0);
	}
	sc->state &= ~PSM_SOFTARMED;

	/* schedule injection of predefined packet after idletimeout
	 * if no data packets have been received from psmintr */
	if (timevalisset(&sc->idletimeout)) {
		sc->state |= PSM_SOFTARMED;
		callout_reset(&sc->softcallout, tvtohz(&sc->idletimeout),
		    psmsoftintridle, sc);
		VLOG(2, (LOG_DEBUG, "softintr: callout set: %d ticks\n",
		    tvtohz(&sc->idletimeout)));
	}
	splx(s);
}