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
struct TYPE_4__ {int /*<<< orphan*/  across_to_list; int /*<<< orphan*/  across_from_list; int /*<<< orphan*/  group_list; } ;
typedef  TYPE_1__ osm_qos_sl2vl_scope_t ;

/* Variables and functions */
 int /*<<< orphan*/  __free_single_element ; 
 int /*<<< orphan*/  cl_list_apply_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_list_remove_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void osm_qos_policy_sl2vl_scope_destroy(osm_qos_sl2vl_scope_t * p)
{
	if (!p)
		return;

	cl_list_apply_func(&p->group_list, __free_single_element, NULL);
	cl_list_apply_func(&p->across_from_list, __free_single_element, NULL);
	cl_list_apply_func(&p->across_to_list, __free_single_element, NULL);

	cl_list_remove_all(&p->group_list);
	cl_list_remove_all(&p->across_from_list);
	cl_list_remove_all(&p->across_to_list);

	cl_list_destroy(&p->group_list);
	cl_list_destroy(&p->across_from_list);
	cl_list_destroy(&p->across_to_list);

	free(p);
}