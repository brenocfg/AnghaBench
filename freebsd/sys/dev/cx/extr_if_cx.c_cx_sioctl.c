#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct ifnet {int if_drv_flags; int if_flags; TYPE_3__* if_softc; } ;
struct TYPE_10__ {TYPE_2__* chan; TYPE_1__* board; } ;
typedef  TYPE_3__ drv_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_9__ {scalar_t__ type; scalar_t__ mode; scalar_t__ debug_shadow; scalar_t__ debug; } ;
struct TYPE_8__ {int /*<<< orphan*/ * sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_DEBUG2 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  CX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CX_UNLOCK (int /*<<< orphan*/ *) ; 
 int EBUSY ; 
 int IFF_DEBUG ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ M_ASYNC ; 
#define  SIOCADDMULTI 131 
#define  SIOCDELMULTI 130 
#define  SIOCSIFADDR 129 
#define  SIOCSIFFLAGS 128 
 scalar_t__ T_NONE ; 
 int /*<<< orphan*/  cx_down (TYPE_3__*) ; 
 int /*<<< orphan*/  cx_start (TYPE_3__*) ; 
 int /*<<< orphan*/  cx_up (TYPE_3__*) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 
 int sppp_ioctl (struct ifnet*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx_sioctl (struct ifnet *ifp, u_long cmd, caddr_t data)
{
	drv_t *d = ifp->if_softc;
	bdrv_t *bd = d->board->sys;
	int error, s, was_up, should_be_up;

	/* No socket ioctls while the channel is in async mode. */
	if (d->chan->type == T_NONE || d->chan->mode == M_ASYNC)
		return EBUSY;

	/* Socket ioctls on slave subchannels are not allowed. */
	was_up = (ifp->if_drv_flags & IFF_DRV_RUNNING) != 0;
	error = sppp_ioctl (ifp, cmd, data);
	if (error)
		return error;

	s = splhigh ();
	CX_LOCK (bd);
	if (! (ifp->if_flags & IFF_DEBUG))
		d->chan->debug = 0;
	else
		d->chan->debug = d->chan->debug_shadow;
	CX_UNLOCK (bd);
	splx (s);

	switch (cmd) {
	default:	   CX_DEBUG2 (d, ("ioctl 0x%lx\n", cmd)); return 0;
	case SIOCADDMULTI: CX_DEBUG2 (d, ("SIOCADDMULTI\n"));     return 0;
	case SIOCDELMULTI: CX_DEBUG2 (d, ("SIOCDELMULTI\n"));     return 0;
	case SIOCSIFFLAGS: CX_DEBUG2 (d, ("SIOCSIFFLAGS\n"));     break;
	case SIOCSIFADDR:  CX_DEBUG2 (d, ("SIOCSIFADDR\n"));      break;
	}

	/* We get here only in case of SIFFLAGS or SIFADDR. */
	s = splhigh ();
	CX_LOCK (bd);
	should_be_up = (ifp->if_drv_flags & IFF_DRV_RUNNING) != 0;
	if (!was_up && should_be_up) {
		/* Interface goes up -- start it. */
		cx_up (d);
		cx_start (d);
	} else if (was_up && !should_be_up) {
		/* Interface is going down -- stop it. */
		/* if ((IFP2SP(d->ifp)->pp_flags & PP_FR) || (ifp->if_flags & PP_CISCO))*/
		cx_down (d);
	}
	CX_UNLOCK (bd);
	splx (s);
	return 0;
}