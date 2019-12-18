#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t num_hca; TYPE_1__* used_link; } ;
typedef  TYPE_2__ vertex_t ;
typedef  size_t uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_log; } ;
typedef  TYPE_3__ osm_ucast_mgr_t ;
struct TYPE_6__ {size_t from; int /*<<< orphan*/  weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_weights(osm_ucast_mgr_t * p_mgr, vertex_t * adj_list,
			   uint32_t adj_list_size)
{
	uint32_t i = 0, j = 0;
	uint32_t additional_weight = 0;

	OSM_LOG_ENTER(p_mgr->p_log);

	for (i = 1; i < adj_list_size; i++) {
		/* if no route goes thru this switch -> cycle */
		if (!(adj_list[i].used_link))
			continue;
		additional_weight = adj_list[i].num_hca;

		j = i;
		while (adj_list[j].used_link) {
			/* update the link from pre to this node */
			adj_list[j].used_link->weight += additional_weight;

			j = adj_list[j].used_link->from;
		}
	}

	OSM_LOG_EXIT(p_mgr->p_log);
}