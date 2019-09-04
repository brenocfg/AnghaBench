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
struct TYPE_3__ {struct TYPE_3__** children; } ;
typedef  TYPE_1__ tmp_node_t ;

/* Variables and functions */

int AAS_CountTmpNodes(tmp_node_t *tmpnode)
{
	if (!tmpnode) return 0;
	return AAS_CountTmpNodes(tmpnode->children[0]) +
				AAS_CountTmpNodes(tmpnode->children[1]) + 1;
}