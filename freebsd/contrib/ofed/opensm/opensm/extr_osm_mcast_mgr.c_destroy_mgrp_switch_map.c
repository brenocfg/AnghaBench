#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ is_mc_member; scalar_t__ num_of_mcm; } ;
typedef  TYPE_1__ osm_switch_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;

/* Variables and functions */
 TYPE_1__* cl_item_obj (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_qmap_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_remove_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgrp_item ; 

__attribute__((used)) static void destroy_mgrp_switch_map(cl_qmap_t * m)
{
	osm_switch_t *sw;
	cl_map_item_t *i;

	for (i = cl_qmap_head(m); i != cl_qmap_end(m); i = cl_qmap_next(i)) {
		sw = cl_item_obj(i, sw, mgrp_item);
		sw->num_of_mcm = 0;
		sw->is_mc_member = 0;
	}
	cl_qmap_remove_all(m);
}