#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ guid; } ;
typedef  TYPE_1__ ibnd_node_t ;
struct TYPE_5__ {scalar_t__ chassisguid; TYPE_1__** spinenode; } ;
typedef  TYPE_2__ ibnd_chassis_t ;

/* Variables and functions */
 int SPINES_MAX_NUM ; 

__attribute__((used)) static void pass_on_spines_interpolate_chguid(ibnd_chassis_t * chassis)
{
	ibnd_node_t *node;
	int i;

	for (i = 1; i <= SPINES_MAX_NUM; i++) {
		node = chassis->spinenode[i];
		if (!node)
			continue;	/* skip the empty slots */

		/* take first guid minus one to be consistent with SM */
		chassis->chassisguid = node->guid - 1;
		break;
	}
}