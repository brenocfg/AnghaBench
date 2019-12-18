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
struct uboot_softc {int /*<<< orphan*/  sc_handle; } ;
struct netif {int /*<<< orphan*/  nif_unit; TYPE_1__* nif_driver; struct uboot_softc* nif_devdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  netif_bname; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ub_dev_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
net_end(struct netif *nif)
{
	struct uboot_softc *sc = nif->nif_devdata;
	int err;

	if ((err = ub_dev_close(sc->sc_handle)) != 0)
		panic("%s%d: net_end failed with error %d",
		    nif->nif_driver->netif_bname, nif->nif_unit, err);
}