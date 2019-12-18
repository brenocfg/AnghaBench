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
struct TYPE_3__ {int /*<<< orphan*/ * res; int /*<<< orphan*/  rid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * res; int /*<<< orphan*/  rid; } ;
struct bnxt_softc {TYPE_1__ doorbell_bar; int /*<<< orphan*/  dev; TYPE_2__ hwrm_bar; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnxt_pci_mapping_free(struct bnxt_softc *softc)
{
	if (softc->hwrm_bar.res != NULL)
		bus_release_resource(softc->dev, SYS_RES_MEMORY,
		    softc->hwrm_bar.rid, softc->hwrm_bar.res);
	softc->hwrm_bar.res = NULL;

	if (softc->doorbell_bar.res != NULL)
		bus_release_resource(softc->dev, SYS_RES_MEMORY,
		    softc->doorbell_bar.rid, softc->doorbell_bar.res);
	softc->doorbell_bar.res = NULL;
}