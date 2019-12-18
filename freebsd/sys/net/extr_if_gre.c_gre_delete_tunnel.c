#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gre_softc {scalar_t__ gre_family; struct gre_softc* gre_so; int /*<<< orphan*/  epoch_ctx; int /*<<< orphan*/  so; int /*<<< orphan*/  list; int /*<<< orphan*/  gre_hdr; } ;
struct gre_socket {scalar_t__ gre_family; struct gre_socket* gre_so; int /*<<< orphan*/  epoch_ctx; int /*<<< orphan*/  so; int /*<<< orphan*/  list; int /*<<< orphan*/  gre_hdr; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 scalar_t__ CK_LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CK_LIST_REMOVE (struct gre_softc*,int /*<<< orphan*/ ) ; 
 TYPE_1__* GRE2IFP (struct gre_softc*) ; 
 int /*<<< orphan*/  GRE_WAIT () ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  M_GRE ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  epoch_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gre_ioctl_sx ; 
 int /*<<< orphan*/  gre_sofree ; 
 int /*<<< orphan*/  if_link_state_change (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_epoch_preempt ; 
 int /*<<< orphan*/  soclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srchash ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gre_delete_tunnel(struct gre_softc *sc)
{
	struct gre_socket *gs;

	sx_assert(&gre_ioctl_sx, SA_XLOCKED);
	if (sc->gre_family != 0) {
		CK_LIST_REMOVE(sc, chain);
		CK_LIST_REMOVE(sc, srchash);
		GRE_WAIT();
		free(sc->gre_hdr, M_GRE);
		sc->gre_family = 0;
	}
	/*
	 * If this Tunnel was the last one that could use UDP socket,
	 * we should unlink socket from hash table and close it.
	 */
	if ((gs = sc->gre_so) != NULL && CK_LIST_EMPTY(&gs->list)) {
		CK_LIST_REMOVE(gs, chain);
		soclose(gs->so);
		epoch_call(net_epoch_preempt, &gs->epoch_ctx, gre_sofree);
		sc->gre_so = NULL;
	}
	GRE2IFP(sc)->if_drv_flags &= ~IFF_DRV_RUNNING;
	if_link_state_change(GRE2IFP(sc), LINK_STATE_DOWN);
}