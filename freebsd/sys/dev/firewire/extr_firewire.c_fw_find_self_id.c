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
struct TYPE_4__ {int phy_id; scalar_t__ sequel; } ;
union fw_self_id {TYPE_2__ p0; } ;
typedef  size_t uint32_t ;
struct firewire_comm {TYPE_1__* topology_map; } ;
struct TYPE_3__ {size_t self_id_count; union fw_self_id* self_id; } ;

/* Variables and functions */

__attribute__((used)) static union fw_self_id *
fw_find_self_id(struct firewire_comm *fc, int node)
{
	uint32_t i;
	union fw_self_id *s;

	for (i = 0; i < fc->topology_map->self_id_count; i++) {
		s = &fc->topology_map->self_id[i];
		if (s->p0.sequel)
			continue;
		if (s->p0.phy_id == node)
			return s;
	}
	return 0;
}