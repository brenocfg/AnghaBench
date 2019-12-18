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
struct nexus_devinfo {int /*<<< orphan*/  ndi_obdinfo; int /*<<< orphan*/  ndi_rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct nexus_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nexus_destroy_dinfo(struct nexus_devinfo *ndi)
{

	resource_list_free(&ndi->ndi_rl);
	ofw_bus_gen_destroy_devinfo(&ndi->ndi_obdinfo);
	free(ndi, M_DEVBUF);
}