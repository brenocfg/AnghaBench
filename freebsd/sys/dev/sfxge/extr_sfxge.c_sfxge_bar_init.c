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
struct TYPE_3__ {int /*<<< orphan*/ * esb_res; int /*<<< orphan*/  esb_handle; int /*<<< orphan*/  esb_tag; int /*<<< orphan*/  esb_rid; } ;
struct sfxge_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  mem_bar; TYPE_1__ bar; } ;
typedef  TYPE_1__ efsys_bar_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SFXGE_BAR_LOCK_INIT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sfxge_bar_init(struct sfxge_softc *sc)
{
	efsys_bar_t *esbp = &sc->bar;

	esbp->esb_rid = PCIR_BAR(sc->mem_bar);
	if ((esbp->esb_res = bus_alloc_resource_any(sc->dev, SYS_RES_MEMORY,
	    &esbp->esb_rid, RF_ACTIVE)) == NULL) {
		device_printf(sc->dev, "Cannot allocate BAR region %d\n",
		    sc->mem_bar);
		return (ENXIO);
	}
	esbp->esb_tag = rman_get_bustag(esbp->esb_res);
	esbp->esb_handle = rman_get_bushandle(esbp->esb_res);

	SFXGE_BAR_LOCK_INIT(esbp, device_get_nameunit(sc->dev));

	return (0);
}