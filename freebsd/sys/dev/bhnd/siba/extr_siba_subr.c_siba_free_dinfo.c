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
typedef  size_t u_int ;
struct TYPE_4__ {int mapped; int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {scalar_t__ intr_en; } ;
struct siba_devinfo {int* cfg_rid; TYPE_2__ intr; TYPE_1__ core_id; int /*<<< orphan*/ ** cfg_res; int /*<<< orphan*/  cfg; int /*<<< orphan*/  resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_BUS_UNMAP_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bhnd_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct siba_devinfo*,int /*<<< orphan*/ ) ; 
 size_t nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 

void
siba_free_dinfo(device_t dev, device_t child, struct siba_devinfo *dinfo)
{
	resource_list_free(&dinfo->resources);

	/* Free all mapped configuration blocks */
	for (u_int i = 0; i < nitems(dinfo->cfg); i++) {
		if (dinfo->cfg_res[i] == NULL)
			continue;

		bhnd_release_resource(dev, SYS_RES_MEMORY, dinfo->cfg_rid[i],
		    dinfo->cfg_res[i]);

		dinfo->cfg_res[i] = NULL;
		dinfo->cfg_rid[i] = -1;
	}

	/* Unmap the core's interrupt */
	if (dinfo->core_id.intr_en && dinfo->intr.mapped) {
		BHND_BUS_UNMAP_INTR(dev, child, dinfo->intr.irq);
		dinfo->intr.mapped = false;
	}

	free(dinfo, M_BHND);
}