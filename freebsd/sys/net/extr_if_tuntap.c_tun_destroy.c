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
struct TYPE_9__ {int /*<<< orphan*/  si_note; } ;
struct tuntap_softc {int tun_flags; scalar_t__ tun_busy; int /*<<< orphan*/  tun_cv; int /*<<< orphan*/  tun_mtx; TYPE_1__* tun_drv; TYPE_2__ tun_rsel; int /*<<< orphan*/  tun_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  if_dunit; int /*<<< orphan*/ * if_softc; int /*<<< orphan*/  if_vnet; } ;
struct TYPE_8__ {int /*<<< orphan*/  unrhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TUN ; 
 TYPE_3__* TUN2IFP (struct tuntap_softc*) ; 
 int TUN_DYING ; 
 int TUN_L2 ; 
 int /*<<< orphan*/  TUN_LOCK (struct tuntap_softc*) ; 
 int /*<<< orphan*/  TUN_UNLOCK (struct tuntap_softc*) ; 
 int /*<<< orphan*/  bpfdetach (TYPE_3__*) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (TYPE_3__*) ; 
 int /*<<< orphan*/  free (struct tuntap_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  if_free (TYPE_3__*) ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seldrain (TYPE_2__*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tun_ioctl_sx ; 

__attribute__((used)) static void
tun_destroy(struct tuntap_softc *tp)
{

	TUN_LOCK(tp);
	tp->tun_flags |= TUN_DYING;
	if (tp->tun_busy != 0)
		cv_wait_unlock(&tp->tun_cv, &tp->tun_mtx);
	else
		TUN_UNLOCK(tp);

	CURVNET_SET(TUN2IFP(tp)->if_vnet);

	/* destroy_dev will take care of any alias. */
	destroy_dev(tp->tun_dev);
	seldrain(&tp->tun_rsel);
	knlist_clear(&tp->tun_rsel.si_note, 0);
	knlist_destroy(&tp->tun_rsel.si_note);
	if ((tp->tun_flags & TUN_L2) != 0) {
		ether_ifdetach(TUN2IFP(tp));
	} else {
		bpfdetach(TUN2IFP(tp));
		if_detach(TUN2IFP(tp));
	}
	sx_xlock(&tun_ioctl_sx);
	TUN2IFP(tp)->if_softc = NULL;
	sx_xunlock(&tun_ioctl_sx);
	free_unr(tp->tun_drv->unrhdr, TUN2IFP(tp)->if_dunit);
	if_free(TUN2IFP(tp));
	mtx_destroy(&tp->tun_mtx);
	cv_destroy(&tp->tun_cv);
	free(tp, M_TUN);
	CURVNET_RESTORE();
}