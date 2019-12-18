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
typedef  int /*<<< orphan*/  osm_mcast_work_obj_t ;
typedef  int /*<<< orphan*/  cl_qlist_t ;

/* Variables and functions */
 scalar_t__ cl_qlist_count (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qlist_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcast_work_obj_delete (int /*<<< orphan*/ *) ; 

void osm_mcast_drop_port_list(cl_qlist_t * list)
{
	while (cl_qlist_count(list))
		mcast_work_obj_delete((osm_mcast_work_obj_t *)
				      cl_qlist_remove_head(list));
}