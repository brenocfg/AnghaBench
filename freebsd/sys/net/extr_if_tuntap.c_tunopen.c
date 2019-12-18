#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  octet; } ;
struct tuntap_softc {int tun_flags; int /*<<< orphan*/  tun_pid; TYPE_1__ tun_ether; } ;
struct thread {TYPE_2__* td_proc; } ;
struct ifnet {int /*<<< orphan*/  if_flags; int /*<<< orphan*/  if_drv_flags; } ;
struct cdev {struct tuntap_softc* si_drv1; int /*<<< orphan*/  si_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  TD_TO_VNET (struct thread*) ; 
 struct ifnet* TUN2IFP (struct tuntap_softc*) ; 
 int /*<<< orphan*/  TUNDEBUG (struct ifnet*,char*) ; 
 int TUN_DYING ; 
 int TUN_INITED ; 
 int TUN_L2 ; 
 int /*<<< orphan*/  TUN_LOCK (struct tuntap_softc*) ; 
 int TUN_OPEN ; 
 int /*<<< orphan*/  TUN_UNLOCK (struct tuntap_softc*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devfs_set_cdevpriv (struct tuntap_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 scalar_t__ tapuponopen ; 
 int tun_busy_locked (struct tuntap_softc*) ; 
 int /*<<< orphan*/  tundtor ; 
 int tuntap_name2info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
tunopen(struct cdev *dev, int flag, int mode, struct thread *td)
{
	struct ifnet	*ifp;
	struct tuntap_softc *tp;
	int error, tunflags;

	tunflags = 0;
	CURVNET_SET(TD_TO_VNET(td));
	error = tuntap_name2info(dev->si_name, NULL, &tunflags);
	if (error != 0) {
		CURVNET_RESTORE();
		return (error);	/* Shouldn't happen */
	}

	tp = dev->si_drv1;
	KASSERT(tp != NULL,
	    ("si_drv1 should have been initialized at creation"));

	TUN_LOCK(tp);
	if ((tp->tun_flags & TUN_INITED) == 0) {
		TUN_UNLOCK(tp);
		CURVNET_RESTORE();
		return (ENXIO);
	}
	if ((tp->tun_flags & (TUN_OPEN | TUN_DYING)) != 0) {
		TUN_UNLOCK(tp);
		CURVNET_RESTORE();
		return (EBUSY);
	}

	error = tun_busy_locked(tp);
	KASSERT(error == 0, ("Must be able to busy an unopen tunnel"));
	ifp = TUN2IFP(tp);

	if ((tp->tun_flags & TUN_L2) != 0) {
		bcopy(IF_LLADDR(ifp), tp->tun_ether.octet,
		    sizeof(tp->tun_ether.octet));

		ifp->if_drv_flags |= IFF_DRV_RUNNING;
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

		if (tapuponopen)
			ifp->if_flags |= IFF_UP;
	}

	tp->tun_pid = td->td_proc->p_pid;
	tp->tun_flags |= TUN_OPEN;

	if_link_state_change(ifp, LINK_STATE_UP);
	TUNDEBUG(ifp, "open\n");
	TUN_UNLOCK(tp);

	/*
	 * This can fail with either ENOENT or EBUSY.  This is in the middle of
	 * d_open, so ENOENT should not be possible.  EBUSY is possible, but
	 * the only cdevpriv dtor being set will be tundtor and the softc being
	 * passed is constant for a given cdev.  We ignore the possible error
	 * because of this as either "unlikely" or "not actually a problem."
	 */
	(void)devfs_set_cdevpriv(tp, tundtor);
	CURVNET_RESTORE();
	return (0);
}