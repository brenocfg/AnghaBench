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
struct lacp_softc {int /*<<< orphan*/  lsc_suppress_distributing; TYPE_2__* lsc_softc; } ;
struct TYPE_4__ {TYPE_1__* sc_ifp; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LACP_LOCK_ASSERT (struct lacp_softc*) ; 
 int /*<<< orphan*/  LACP_TRACE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lacp_transit_expire(void *vp)
{
	struct lacp_softc *lsc = vp;

	LACP_LOCK_ASSERT(lsc);

	CURVNET_SET(lsc->lsc_softc->sc_ifp->if_vnet);
	LACP_TRACE(NULL);
	CURVNET_RESTORE();

	lsc->lsc_suppress_distributing = FALSE;
}