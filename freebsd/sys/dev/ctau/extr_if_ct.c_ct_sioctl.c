#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct ifnet {int if_drv_flags; int if_flags; TYPE_2__* if_softc; } ;
struct TYPE_8__ {TYPE_1__* chan; int /*<<< orphan*/ * bd; } ;
typedef  TYPE_2__ drv_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_7__ {scalar_t__ debug_shadow; scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_DEBUG2 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  CT_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CT_UNLOCK (int /*<<< orphan*/ *) ; 
 int IFF_DEBUG ; 
 int IFF_DRV_RUNNING ; 
#define  SIOCADDMULTI 131 
#define  SIOCDELMULTI 130 
#define  SIOCSIFADDR 129 
#define  SIOCSIFFLAGS 128 
 int /*<<< orphan*/  ct_down (TYPE_2__*) ; 
 int /*<<< orphan*/  ct_start (TYPE_2__*) ; 
 int /*<<< orphan*/  ct_up (TYPE_2__*) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 
 int sppp_ioctl (struct ifnet*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ct_sioctl (struct ifnet *ifp, u_long cmd, caddr_t data)
{
	drv_t *d = ifp->if_softc;
	bdrv_t *bd = d->bd;
	int error, s, was_up, should_be_up;

	was_up = (ifp->if_drv_flags & IFF_DRV_RUNNING) != 0;
	error = sppp_ioctl (ifp, cmd, data);
	if (error)
		return error;

	if (! (ifp->if_flags & IFF_DEBUG))
		d->chan->debug = 0;
	else
		d->chan->debug = d->chan->debug_shadow;

	switch (cmd) {
	default:	   CT_DEBUG2 (d, ("ioctl 0x%lx\n", cmd)); return 0;
	case SIOCADDMULTI: CT_DEBUG2 (d, ("SIOCADDMULTI\n"));     return 0;
	case SIOCDELMULTI: CT_DEBUG2 (d, ("SIOCDELMULTI\n"));     return 0;
	case SIOCSIFFLAGS: CT_DEBUG2 (d, ("SIOCSIFFLAGS\n"));     break;
	case SIOCSIFADDR:  CT_DEBUG2 (d, ("SIOCSIFADDR\n"));      break;
	}

	/* We get here only in case of SIFFLAGS or SIFADDR. */
	s = splimp ();
	CT_LOCK (bd);
	should_be_up = (ifp->if_drv_flags & IFF_DRV_RUNNING) != 0;
	if (! was_up && should_be_up) {
		/* Interface goes up -- start it. */
		ct_up (d);
		ct_start (d);
	} else if (was_up && ! should_be_up) {
		/* Interface is going down -- stop it. */
		/* if ((IFP2SP(d->ifp)->pp_flags & PP_FR) || (ifp->if_flags & PP_CISCO))*/
		ct_down (d);
	}
	CT_UNLOCK (bd);
	splx (s);
	return 0;
}