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
struct TYPE_3__ {int /*<<< orphan*/  across_to_list; int /*<<< orphan*/  across_from_list; int /*<<< orphan*/  group_list; } ;
typedef  TYPE_1__ osm_qos_sl2vl_scope_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  cl_list_init (int /*<<< orphan*/ *,int) ; 

osm_qos_sl2vl_scope_t *osm_qos_policy_sl2vl_scope_create()
{
	osm_qos_sl2vl_scope_t *p =
	    (osm_qos_sl2vl_scope_t *) calloc(1, sizeof(osm_qos_sl2vl_scope_t));
	if (p) {
		cl_list_init(&p->group_list, 10);
		cl_list_init(&p->across_from_list, 10);
		cl_list_init(&p->across_to_list, 10);
	}
	return p;
}