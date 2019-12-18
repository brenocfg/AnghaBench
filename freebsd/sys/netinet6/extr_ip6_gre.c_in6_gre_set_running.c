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
struct TYPE_3__ {int /*<<< orphan*/  ip6_src; } ;
struct gre_softc {TYPE_1__ gre_oip6; } ;
struct TYPE_4__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 TYPE_2__* GRE2IFP (struct gre_softc*) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 scalar_t__ in6_localip (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
in6_gre_set_running(struct gre_softc *sc)
{

	if (in6_localip(&sc->gre_oip6.ip6_src))
		GRE2IFP(sc)->if_drv_flags |= IFF_DRV_RUNNING;
	else
		GRE2IFP(sc)->if_drv_flags &= ~IFF_DRV_RUNNING;
}