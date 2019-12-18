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
struct tuntap_softc {int tun_flags; scalar_t__ tun_sigio; TYPE_1__ tun_rsel; } ;
struct mbuf {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_snd; struct tuntap_softc* if_softc; } ;

/* Variables and functions */
 scalar_t__ ALTQ_IS_ENABLED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_POLL_NOLOCK (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  TUNDEBUG (struct ifnet*,char*) ; 
 int TUN_ASYNC ; 
 int /*<<< orphan*/  TUN_LOCK (struct tuntap_softc*) ; 
 int TUN_RWAIT ; 
 int /*<<< orphan*/  TUN_UNLOCK (struct tuntap_softc*) ; 
 int /*<<< orphan*/  pgsigio (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  wakeup (struct tuntap_softc*) ; 

__attribute__((used)) static void
tunstart(struct ifnet *ifp)
{
	struct tuntap_softc *tp = ifp->if_softc;
	struct mbuf *m;

	TUNDEBUG(ifp, "starting\n");
	if (ALTQ_IS_ENABLED(&ifp->if_snd)) {
		IFQ_LOCK(&ifp->if_snd);
		IFQ_POLL_NOLOCK(&ifp->if_snd, m);
		if (m == NULL) {
			IFQ_UNLOCK(&ifp->if_snd);
			return;
		}
		IFQ_UNLOCK(&ifp->if_snd);
	}

	TUN_LOCK(tp);
	if (tp->tun_flags & TUN_RWAIT) {
		tp->tun_flags &= ~TUN_RWAIT;
		wakeup(tp);
	}
	selwakeuppri(&tp->tun_rsel, PZERO + 1);
	KNOTE_LOCKED(&tp->tun_rsel.si_note, 0);
	if (tp->tun_flags & TUN_ASYNC && tp->tun_sigio) {
		TUN_UNLOCK(tp);
		pgsigio(&tp->tun_sigio, SIGIO, 0);
	} else
		TUN_UNLOCK(tp);
}