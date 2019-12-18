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
struct lebuffer_devinfo {int /*<<< orphan*/  ldi_obdinfo; int /*<<< orphan*/  ldi_rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct lebuffer_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lebuffer_destroy_dinfo(struct lebuffer_devinfo *dinfo)
{

	resource_list_free(&dinfo->ldi_rl);
	ofw_bus_gen_destroy_devinfo(&dinfo->ldi_obdinfo);
	free(dinfo, M_DEVBUF);
}