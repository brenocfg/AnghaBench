#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ s_addr; } ;
struct TYPE_5__ {scalar_t__ s_addr; } ;
struct me_softc {TYPE_2__ me_dst; TYPE_1__ me_src; } ;
struct TYPE_7__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_REMOVE (struct me_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 TYPE_3__* ME2IFP (struct me_softc*) ; 
 scalar_t__ ME_READY (struct me_softc*) ; 
 int /*<<< orphan*/  ME_WAIT () ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  if_link_state_change (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  me_ioctl_sx ; 
 int /*<<< orphan*/  srchash ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
me_delete_tunnel(struct me_softc *sc)
{

	sx_assert(&me_ioctl_sx, SA_XLOCKED);
	if (ME_READY(sc)) {
		CK_LIST_REMOVE(sc, chain);
		CK_LIST_REMOVE(sc, srchash);
		ME_WAIT();

		sc->me_src.s_addr = 0;
		sc->me_dst.s_addr = 0;
		ME2IFP(sc)->if_drv_flags &= ~IFF_DRV_RUNNING;
		if_link_state_change(ME2IFP(sc), LINK_STATE_DOWN);
	}
}