#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* to_node_id; int /*<<< orphan*/  total; int /*<<< orphan*/ * per_node; } ;

/* Variables and functions */
 int NODE_ID_FREE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* emu_cores ; 

__attribute__((used)) static void pin_core_to_node(int core_id, int node_id)
{
	if (emu_cores->to_node_id[core_id] == NODE_ID_FREE) {
		emu_cores->per_node[node_id]++;
		emu_cores->to_node_id[core_id] = node_id;
		emu_cores->total++;
	} else {
		WARN_ON(emu_cores->to_node_id[core_id] != node_id);
	}
}