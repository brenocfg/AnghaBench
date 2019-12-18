#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ch_slot; size_t ch_slotnum; TYPE_2__* chassis; } ;
typedef  TYPE_1__ ibnd_node_t ;
struct TYPE_6__ {TYPE_1__** spinenode; TYPE_1__** linenode; } ;
typedef  TYPE_2__ ibnd_chassis_t ;

/* Variables and functions */
 scalar_t__ LINE_CS ; 
 scalar_t__ SPINE_CS ; 

__attribute__((used)) static int insert_mellanox_line_and_spine(ibnd_node_t * node, ibnd_chassis_t * chassis)
{
	if (node->ch_slot == LINE_CS){

		if (chassis->linenode[node->ch_slotnum])
			return 0;	/* already filled slot */

		chassis->linenode[node->ch_slotnum] = node;
	}
	else if (node->ch_slot == SPINE_CS){

		if (chassis->spinenode[node->ch_slotnum])
			return 0;	/* already filled slot */

		chassis->spinenode[node->ch_slotnum] = node;
	}
	else
		return 0;

	node->chassis = chassis;

	return 0;
}