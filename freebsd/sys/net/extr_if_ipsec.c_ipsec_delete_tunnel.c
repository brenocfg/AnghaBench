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
struct ipsec_softc {scalar_t__ family; int /*<<< orphan*/ * sp; TYPE_1__* ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_REMOVE (struct ipsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IPSEC_SPCOUNT ; 
 int /*<<< orphan*/  IPSEC_WAIT () ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  ipsec_ioctl_sx ; 
 int /*<<< orphan*/  key_freesp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_unregister_ifnet (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  srchash ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipsec_delete_tunnel(struct ipsec_softc *sc)
{
	int i;

	sx_assert(&ipsec_ioctl_sx, SA_XLOCKED);

	sc->ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	if (sc->family != 0) {
		CK_LIST_REMOVE(sc, srchash);
		sc->family = 0;
		/*
		 * Make sure that ipsec_if_input() will not do access
		 * to softc's policies.
		 */
		IPSEC_WAIT();

		key_unregister_ifnet(sc->sp, IPSEC_SPCOUNT);
		for (i = 0; i < IPSEC_SPCOUNT; i++)
			key_freesp(&sc->sp[i]);
	}
}