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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct tuntap_softc {int tun_flags; TYPE_1__ tun_rsel; int /*<<< orphan*/ * tun_sigio; } ;
struct mbuf {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; int /*<<< orphan*/  if_snd; struct tuntap_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFQ_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  TUNDEBUG (struct ifnet*,char*,...) ; 
 int TUN_ASYNC ; 
 int /*<<< orphan*/  TUN_LOCK (struct tuntap_softc*) ; 
 int TUN_READY ; 
 int TUN_RWAIT ; 
 int /*<<< orphan*/  TUN_UNLOCK (struct tuntap_softc*) ; 
 int TUN_VMNET ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  pgsigio (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  wakeup (struct tuntap_softc*) ; 

__attribute__((used)) static void
tunstart_l2(struct ifnet *ifp)
{
	struct tuntap_softc	*tp = ifp->if_softc;

	TUNDEBUG(ifp, "starting\n");

	/*
	 * do not junk pending output if we are in VMnet mode.
	 * XXX: can this do any harm because of queue overflow?
	 */

	TUN_LOCK(tp);
	if (((tp->tun_flags & TUN_VMNET) == 0) &&
	    ((tp->tun_flags & TUN_READY) != TUN_READY)) {
		struct mbuf *m;

		/* Unlocked read. */
		TUNDEBUG(ifp, "not ready, tun_flags = 0x%x\n", tp->tun_flags);

		for (;;) {
			IF_DEQUEUE(&ifp->if_snd, m);
			if (m != NULL) {
				m_freem(m);
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			} else
				break;
		}
		TUN_UNLOCK(tp);

		return;
	}

	ifp->if_drv_flags |= IFF_DRV_OACTIVE;

	if (!IFQ_IS_EMPTY(&ifp->if_snd)) {
		if (tp->tun_flags & TUN_RWAIT) {
			tp->tun_flags &= ~TUN_RWAIT;
			wakeup(tp);
		}

		if ((tp->tun_flags & TUN_ASYNC) && (tp->tun_sigio != NULL)) {
			TUN_UNLOCK(tp);
			pgsigio(&tp->tun_sigio, SIGIO, 0);
			TUN_LOCK(tp);
		}

		selwakeuppri(&tp->tun_rsel, PZERO+1);
		KNOTE_LOCKED(&tp->tun_rsel.si_note, 0);
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1); /* obytes are counted in ether_output */
	}

	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	TUN_UNLOCK(tp);
}