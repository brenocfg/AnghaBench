#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dma_devinfo {int /*<<< orphan*/  ddi_obdinfo; int /*<<< orphan*/  ddi_rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct dma_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dma_destroy_dinfo(struct dma_devinfo *dinfo)
{

	resource_list_free(&dinfo->ddi_rl);
	ofw_bus_gen_destroy_devinfo(&dinfo->ddi_obdinfo);
	free(dinfo, M_DEVBUF);
}