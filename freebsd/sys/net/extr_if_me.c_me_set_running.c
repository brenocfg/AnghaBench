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
struct me_softc {int /*<<< orphan*/  me_src; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 TYPE_1__* ME2IFP (struct me_softc*) ; 
 scalar_t__ in_localip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
me_set_running(struct me_softc *sc)
{

	if (in_localip(sc->me_src))
		ME2IFP(sc)->if_drv_flags |= IFF_DRV_RUNNING;
	else
		ME2IFP(sc)->if_drv_flags &= ~IFF_DRV_RUNNING;
}