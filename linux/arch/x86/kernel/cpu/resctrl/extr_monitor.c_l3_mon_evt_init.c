#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rdt_resource {int /*<<< orphan*/  evt_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ is_llc_occupancy_enabled () ; 
 scalar_t__ is_mbm_local_enabled () ; 
 scalar_t__ is_mbm_total_enabled () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__ llc_occupancy_event ; 
 TYPE_2__ mbm_local_event ; 
 TYPE_1__ mbm_total_event ; 

__attribute__((used)) static void l3_mon_evt_init(struct rdt_resource *r)
{
	INIT_LIST_HEAD(&r->evt_list);

	if (is_llc_occupancy_enabled())
		list_add_tail(&llc_occupancy_event.list, &r->evt_list);
	if (is_mbm_total_enabled())
		list_add_tail(&mbm_total_event.list, &r->evt_list);
	if (is_mbm_local_enabled())
		list_add_tail(&mbm_local_event.list, &r->evt_list);
}