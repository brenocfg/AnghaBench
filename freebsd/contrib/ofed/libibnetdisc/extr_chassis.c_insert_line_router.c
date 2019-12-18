#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* chassis; } ;
typedef  TYPE_1__ ibnd_node_t ;
struct TYPE_7__ {TYPE_1__** linenode; } ;
typedef  TYPE_2__ ibnd_chassis_t ;

/* Variables and functions */
 int get_line_index (TYPE_1__*) ; 

__attribute__((used)) static int insert_line_router(ibnd_node_t * node, ibnd_chassis_t * chassis)
{
	int i = get_line_index(node);

	if (i < 0)
		return i;

	if (chassis->linenode[i])
		return 0;	/* already filled slot */

	chassis->linenode[i] = node;
	node->chassis = chassis;
	return 0;
}