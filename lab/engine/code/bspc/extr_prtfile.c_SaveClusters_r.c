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
struct TYPE_4__ {scalar_t__ planenum; struct TYPE_4__** children; int /*<<< orphan*/  cluster; } ;
typedef  TYPE_1__ node_t ;
struct TYPE_5__ {int /*<<< orphan*/  cluster; } ;

/* Variables and functions */
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  clusterleaf ; 
 TYPE_2__* dleafs ; 

void SaveClusters_r (node_t *node)
{
	if (node->planenum == PLANENUM_LEAF)
	{
		dleafs[clusterleaf++].cluster = node->cluster;
		return;
	}
	SaveClusters_r (node->children[0]);
	SaveClusters_r (node->children[1]);
}