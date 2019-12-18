#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_22__ ;
typedef  struct TYPE_25__   TYPE_21__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct serial_statistics {int /*<<< orphan*/  oerrs; int /*<<< orphan*/  opkts; int /*<<< orphan*/  obytes; int /*<<< orphan*/  ierrs; int /*<<< orphan*/  ipkts; int /*<<< orphan*/  ibytes; int /*<<< orphan*/  mintr; int /*<<< orphan*/  tintr; int /*<<< orphan*/  rintr; } ;
struct cdev {TYPE_3__* si_drv1; } ;
typedef  int /*<<< orphan*/  mask ;
struct TYPE_28__ {int open_dev; TYPE_22__* ifp; int /*<<< orphan*/  running; TYPE_2__* tty; int /*<<< orphan*/  lock; TYPE_1__* board; TYPE_4__* chan; } ;
typedef  TYPE_3__ drv_t ;
struct TYPE_29__ {int debug; int debug_shadow; int /*<<< orphan*/  mode; int /*<<< orphan*/  oerrs; int /*<<< orphan*/  opkts; int /*<<< orphan*/  obytes; int /*<<< orphan*/  ierrs; int /*<<< orphan*/  ipkts; int /*<<< orphan*/  ibytes; int /*<<< orphan*/  mintr; int /*<<< orphan*/  tintr; int /*<<< orphan*/  rintr; } ;
typedef  TYPE_4__ cx_chan_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_27__ {int t_state; } ;
struct TYPE_26__ {int if_flags; int if_drv_flags; } ;
struct TYPE_25__ {int pp_flags; } ;
struct TYPE_24__ {int /*<<< orphan*/ * sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_DEBUG2 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  CX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CX_UNLOCK (int /*<<< orphan*/ *) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOTTY ; 
 int IFF_DEBUG ; 
 int IFF_DRV_RUNNING ; 
 TYPE_21__* IFP2SP (TYPE_22__*) ; 
 int /*<<< orphan*/  M_ASYNC ; 
 int /*<<< orphan*/  M_HDLC ; 
 int NCHAN ; 
 int NCX ; 
 int PP_CISCO ; 
 int PP_FR ; 
 int PP_KEEPALIVE ; 
 int /*<<< orphan*/  PRIV_DRIVER ; 
 int SERIAL_ASYNC ; 
#define  SERIAL_CLRSTAT 154 
#define  SERIAL_GETBAUD 153 
#define  SERIAL_GETDEBUG 152 
#define  SERIAL_GETDPLL 151 
#define  SERIAL_GETKEEPALIVE 150 
#define  SERIAL_GETLOOP 149 
#define  SERIAL_GETMODE 148 
#define  SERIAL_GETNRZI 147 
#define  SERIAL_GETPORT 146 
#define  SERIAL_GETPROTO 145 
#define  SERIAL_GETREGISTERED 144 
#define  SERIAL_GETSTAT 143 
 int SERIAL_HDLC ; 
#define  SERIAL_SETBAUD 142 
#define  SERIAL_SETDEBUG 141 
#define  SERIAL_SETDPLL 140 
#define  SERIAL_SETKEEPALIVE 139 
#define  SERIAL_SETLOOP 138 
#define  SERIAL_SETMODE 137 
#define  SERIAL_SETNRZI 136 
#define  SERIAL_SETPORT 135 
#define  SERIAL_SETPROTO 134 
#define  TIOCCDTR 133 
#define  TIOCMBIC 132 
#define  TIOCMBIS 131 
#define  TIOCMGET 130 
#define  TIOCMSET 129 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
#define  TIOCSDTR 128 
 int TS_ISOPEN ; 
 int /*<<< orphan*/  bcopy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/ * channel ; 
 int /*<<< orphan*/  cx_enable_receive (TYPE_4__*,int) ; 
 int /*<<< orphan*/  cx_enable_transmit (TYPE_4__*,int) ; 
 long cx_get_baud (TYPE_4__*) ; 
 int cx_get_dpll (TYPE_4__*) ; 
 int cx_get_loop (TYPE_4__*) ; 
 int cx_get_nrzi (TYPE_4__*) ; 
 int cx_get_port (TYPE_4__*) ; 
 int cx_modem_status (TYPE_3__*) ; 
 int /*<<< orphan*/  cx_set_baud (TYPE_4__*,long) ; 
 int /*<<< orphan*/  cx_set_dpll (TYPE_4__*,int) ; 
 int /*<<< orphan*/  cx_set_dtr (TYPE_4__*,int) ; 
 int /*<<< orphan*/  cx_set_loop (TYPE_4__*,int) ; 
 int /*<<< orphan*/  cx_set_mode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_set_nrzi (TYPE_4__*,int) ; 
 int /*<<< orphan*/  cx_set_port (TYPE_4__*,int) ; 
 int /*<<< orphan*/  cx_set_rts (TYPE_4__*,int) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int cx_ioctl (struct cdev *dev, u_long cmd, caddr_t data, int flag, struct thread *td)
{
	drv_t *d;
	bdrv_t *bd;
	cx_chan_t *c;
	struct serial_statistics *st;
	int error, s;
	char mask[16];

	d = dev->si_drv1;
	c = d->chan;
		
	bd = d->board->sys;
	
	switch (cmd) {
	case SERIAL_GETREGISTERED:
		CX_DEBUG2 (d, ("ioctl: getregistered\n"));
		bzero (mask, sizeof(mask));
		for (s=0; s<NCX*NCHAN; ++s)
			if (channel [s])
				mask [s/8] |= 1 << (s & 7);
		bcopy (mask, data, sizeof (mask));
		return 0;

	case SERIAL_GETPORT:
		CX_DEBUG2 (d, ("ioctl: getport\n"));
		s = splhigh ();
		CX_LOCK (bd);
		*(int *)data = cx_get_port (c);
		CX_UNLOCK (bd);
		splx (s);
		if (*(int *)data<0)
			return (EINVAL);
		else
			return 0;

	case SERIAL_SETPORT:
		CX_DEBUG2 (d, ("ioctl: setproto\n"));
		/* Only for superuser! */
		error = priv_check (td, PRIV_DRIVER);
		if (error)
			return error;

		s = splhigh ();
		CX_LOCK (bd);
		cx_set_port (c, *(int *)data);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

#ifndef NETGRAPH
	case SERIAL_GETPROTO:
		CX_DEBUG2 (d, ("ioctl: getproto\n"));
		s = splhigh ();
		CX_LOCK (bd);
		strcpy ((char*)data, (c->mode == M_ASYNC) ? "async" :
			(IFP2SP(d->ifp)->pp_flags & PP_FR) ? "fr" :
			(d->ifp->if_flags & PP_CISCO) ? "cisco" : "ppp");
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_SETPROTO:
		CX_DEBUG2 (d, ("ioctl: setproto\n"));
		/* Only for superuser! */
		error = priv_check (td, PRIV_DRIVER);
		if (error)
			return error;
		if (c->mode == M_ASYNC)
			return EBUSY;
		if (d->ifp->if_drv_flags & IFF_DRV_RUNNING)
			return EBUSY;
		if (! strcmp ("cisco", (char*)data)) {
			IFP2SP(d->ifp)->pp_flags &= ~(PP_FR);
			IFP2SP(d->ifp)->pp_flags |= PP_KEEPALIVE;
			d->ifp->if_flags |= PP_CISCO;
		} else if (! strcmp ("fr", (char*)data)) {
			d->ifp->if_flags &= ~(PP_CISCO);
			IFP2SP(d->ifp)->pp_flags |= PP_FR | PP_KEEPALIVE;
		} else if (! strcmp ("ppp", (char*)data)) {
			IFP2SP(d->ifp)->pp_flags &= ~(PP_FR | PP_KEEPALIVE);
			d->ifp->if_flags &= ~(PP_CISCO);
		} else
			return EINVAL;
		return 0;

	case SERIAL_GETKEEPALIVE:
		CX_DEBUG2 (d, ("ioctl: getkeepalive\n"));
		if ((IFP2SP(d->ifp)->pp_flags & PP_FR) ||
		    (d->ifp->if_flags & PP_CISCO) ||
		    (c->mode == M_ASYNC))
			return EINVAL;
		s = splhigh ();
		CX_LOCK (bd);
		*(int*)data = (IFP2SP(d->ifp)->pp_flags & PP_KEEPALIVE) ? 1 : 0;
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_SETKEEPALIVE:
		CX_DEBUG2 (d, ("ioctl: setkeepalive\n"));
		/* Only for superuser! */
		error = priv_check (td, PRIV_DRIVER);
		if (error)
			return error;
		if ((IFP2SP(d->ifp)->pp_flags & PP_FR) ||
			(d->ifp->if_flags & PP_CISCO))
			return EINVAL;
		s = splhigh ();
		CX_LOCK (bd);
		if (*(int*)data)
			IFP2SP(d->ifp)->pp_flags |= PP_KEEPALIVE;
		else
			IFP2SP(d->ifp)->pp_flags &= ~PP_KEEPALIVE;
		CX_UNLOCK (bd);
		splx (s);
		return 0;
#endif /*NETGRAPH*/

	case SERIAL_GETMODE:
		CX_DEBUG2 (d, ("ioctl: getmode\n"));
		s = splhigh ();
		CX_LOCK (bd);
		*(int*)data = (c->mode == M_ASYNC) ?
			SERIAL_ASYNC : SERIAL_HDLC;
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_SETMODE:
		CX_DEBUG2 (d, ("ioctl: setmode\n"));
		/* Only for superuser! */
		error = priv_check (td, PRIV_DRIVER);
		if (error)
			return error;

		/* Somebody is waiting for carrier? */
		if (d->lock)
			return EBUSY;
		/* /dev/ttyXX is already opened by someone? */
		if (c->mode == M_ASYNC && d->tty && (d->tty->t_state & TS_ISOPEN) &&
		    (d->open_dev|0x2))
			return EBUSY;
		/* Network interface is up?
		 * Cannot change to async mode. */
		if (c->mode != M_ASYNC && d->running &&
		    (*(int*)data == SERIAL_ASYNC))
			return EBUSY;

		s = splhigh ();
		CX_LOCK (bd);
		if (c->mode == M_HDLC && *(int*)data == SERIAL_ASYNC) {
			cx_set_mode (c, M_ASYNC);
			cx_enable_receive (c, 0);
			cx_enable_transmit (c, 0);
		} else if (c->mode == M_ASYNC && *(int*)data == SERIAL_HDLC) {
			if (d->ifp->if_flags & IFF_DEBUG)
				c->debug = c->debug_shadow;
			cx_set_mode (c, M_HDLC);
			cx_enable_receive (c, 1);
			cx_enable_transmit (c, 1);
		}
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_GETSTAT:
		CX_DEBUG2 (d, ("ioctl: getestat\n"));
		st = (struct serial_statistics*) data;
		s = splhigh ();
		CX_LOCK (bd);
		st->rintr  = c->rintr;
		st->tintr  = c->tintr;
		st->mintr  = c->mintr;
		st->ibytes = c->ibytes;
		st->ipkts  = c->ipkts;
		st->ierrs  = c->ierrs;
		st->obytes = c->obytes;
		st->opkts  = c->opkts;
		st->oerrs  = c->oerrs;
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_CLRSTAT:
		CX_DEBUG2 (d, ("ioctl: clrstat\n"));
		/* Only for superuser! */
		error = priv_check (td, PRIV_DRIVER);
		if (error)
			return error;
		s = splhigh ();
		CX_LOCK (bd);
		c->rintr = 0;
		c->tintr = 0;
		c->mintr = 0;
		c->ibytes = 0;
		c->ipkts = 0;
		c->ierrs = 0;
		c->obytes = 0;
		c->opkts = 0;
		c->oerrs = 0;
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_GETBAUD:
		CX_DEBUG2 (d, ("ioctl: getbaud\n"));
		if (c->mode == M_ASYNC)
			return EINVAL;
		s = splhigh ();
		CX_LOCK (bd);
		*(long*)data = cx_get_baud(c);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_SETBAUD:
		CX_DEBUG2 (d, ("ioctl: setbaud\n"));
		/* Only for superuser! */
		error = priv_check (td, PRIV_DRIVER);
		if (error)
			return error;
		if (c->mode == M_ASYNC)
			return EINVAL;
		s = splhigh ();
		CX_LOCK (bd);
		cx_set_baud (c, *(long*)data);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_GETLOOP:
		CX_DEBUG2 (d, ("ioctl: getloop\n"));
		if (c->mode == M_ASYNC)
			return EINVAL;
		s = splhigh ();
		CX_LOCK (bd);
		*(int*)data = cx_get_loop (c);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_SETLOOP:
		CX_DEBUG2 (d, ("ioctl: setloop\n"));
		/* Only for superuser! */
		error = priv_check (td, PRIV_DRIVER);
		if (error)
			return error;
		if (c->mode == M_ASYNC)
			return EINVAL;
		s = splhigh ();
		CX_LOCK (bd);
		cx_set_loop (c, *(int*)data);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_GETDPLL:
		CX_DEBUG2 (d, ("ioctl: getdpll\n"));
		if (c->mode == M_ASYNC)
			return EINVAL;
		s = splhigh ();
		CX_LOCK (bd);
		*(int*)data = cx_get_dpll (c);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_SETDPLL:
		CX_DEBUG2 (d, ("ioctl: setdpll\n"));
		/* Only for superuser! */
		error = priv_check (td, PRIV_DRIVER);
		if (error)
			return error;
		if (c->mode == M_ASYNC)
			return EINVAL;
		s = splhigh ();
		CX_LOCK (bd);
		cx_set_dpll (c, *(int*)data);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_GETNRZI:
		CX_DEBUG2 (d, ("ioctl: getnrzi\n"));
		if (c->mode == M_ASYNC)
			return EINVAL;
		s = splhigh ();
		CX_LOCK (bd);
		*(int*)data = cx_get_nrzi (c);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_SETNRZI:
		CX_DEBUG2 (d, ("ioctl: setnrzi\n"));
		/* Only for superuser! */
		error = priv_check (td, PRIV_DRIVER);
		if (error)
			return error;
		if (c->mode == M_ASYNC)
			return EINVAL;
		s = splhigh ();
		CX_LOCK (bd);
		cx_set_nrzi (c, *(int*)data);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_GETDEBUG:
		CX_DEBUG2 (d, ("ioctl: getdebug\n"));
		s = splhigh ();
		CX_LOCK (bd);
		*(int*)data = c->debug;
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case SERIAL_SETDEBUG:
		CX_DEBUG2 (d, ("ioctl: setdebug\n"));
		/* Only for superuser! */
		error = priv_check (td, PRIV_DRIVER);
		if (error)
			return error;
		s = splhigh ();
		CX_LOCK (bd);
#ifndef	NETGRAPH
		if (c->mode == M_ASYNC) {
			c->debug = *(int*)data;
		} else {
			/*
			 * The debug_shadow is always greater than zero for
			 * logic simplicity.  For switching debug off the
			 * IFF_DEBUG is responsible (for !M_ASYNC mode).
			 */
			c->debug_shadow = (*(int*)data) ? (*(int*)data) : 1;
			if (d->ifp->if_flags & IFF_DEBUG)
				c->debug = c->debug_shadow;
		}
#else
		c->debug = *(int*)data;
#endif
		CX_UNLOCK (bd);
		splx (s);
		return 0;
	}

	switch (cmd) {
	case TIOCSDTR:	/* Set DTR */
		CX_DEBUG2 (d, ("ioctl: tiocsdtr\n"));
		s = splhigh ();
		CX_LOCK (bd);
		cx_set_dtr (c, 1);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case TIOCCDTR:	/* Clear DTR */
		CX_DEBUG2 (d, ("ioctl: tioccdtr\n"));
		s = splhigh ();
		CX_LOCK (bd);
		cx_set_dtr (c, 0);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case TIOCMSET:	/* Set DTR/RTS */
		CX_DEBUG2 (d, ("ioctl: tiocmset\n"));
		s = splhigh ();
		CX_LOCK (bd);
		cx_set_dtr (c, (*(int*)data & TIOCM_DTR) ? 1 : 0);
		cx_set_rts (c, (*(int*)data & TIOCM_RTS) ? 1 : 0);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case TIOCMBIS:	/* Add DTR/RTS */
		CX_DEBUG2 (d, ("ioctl: tiocmbis\n"));
		s = splhigh ();
		CX_LOCK (bd);
		if (*(int*)data & TIOCM_DTR) cx_set_dtr (c, 1);
		if (*(int*)data & TIOCM_RTS) cx_set_rts (c, 1);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case TIOCMBIC:	/* Clear DTR/RTS */
		CX_DEBUG2 (d, ("ioctl: tiocmbic\n"));
		s = splhigh ();
		CX_LOCK (bd);
		if (*(int*)data & TIOCM_DTR) cx_set_dtr (c, 0);
		if (*(int*)data & TIOCM_RTS) cx_set_rts (c, 0);
		CX_UNLOCK (bd);
		splx (s);
		return 0;

	case TIOCMGET:	/* Get modem status */
		CX_DEBUG2 (d, ("ioctl: tiocmget\n"));
		*(int*)data = cx_modem_status (d);
		return 0;

	}

	CX_DEBUG2 (d, ("ioctl: 0x%lx\n", cmd));
	return ENOTTY;
}