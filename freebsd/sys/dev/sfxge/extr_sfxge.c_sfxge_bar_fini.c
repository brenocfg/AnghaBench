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
struct TYPE_3__ {int /*<<< orphan*/  esb_res; int /*<<< orphan*/  esb_rid; } ;
struct sfxge_softc {int /*<<< orphan*/  dev; TYPE_1__ bar; } ;
typedef  TYPE_1__ efsys_bar_t ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_BAR_LOCK_DESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sfxge_bar_fini(struct sfxge_softc *sc)
{
	efsys_bar_t *esbp = &sc->bar;

	bus_release_resource(sc->dev, SYS_RES_MEMORY, esbp->esb_rid,
	    esbp->esb_res);
	SFXGE_BAR_LOCK_DESTROY(esbp);
}