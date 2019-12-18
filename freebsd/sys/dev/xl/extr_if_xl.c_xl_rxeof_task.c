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
struct xl_softc {TYPE_1__* xl_ifp; } ;
struct TYPE_2__ {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  XL_LOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  XL_UNLOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  xl_rxeof (struct xl_softc*) ; 

__attribute__((used)) static void
xl_rxeof_task(void *arg, int pending)
{
	struct xl_softc *sc = (struct xl_softc *)arg;

	XL_LOCK(sc);
	if (sc->xl_ifp->if_drv_flags & IFF_DRV_RUNNING)
		xl_rxeof(sc);
	XL_UNLOCK(sc);
}