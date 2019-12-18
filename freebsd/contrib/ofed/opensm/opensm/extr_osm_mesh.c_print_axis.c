#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int* axes; TYPE_4__** links; } ;
typedef  TYPE_5__ mesh_node_t ;
struct TYPE_13__ {TYPE_3__** switches; } ;
typedef  TYPE_6__ lash_t ;
struct TYPE_11__ {size_t switch_id; } ;
struct TYPE_10__ {TYPE_2__* p_sw; TYPE_5__* node; } ;
struct TYPE_9__ {TYPE_1__* p_node; } ;
struct TYPE_8__ {char* print_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void print_axis(lash_t *p_lash, char *p, int sw, int port)
{
	mesh_node_t *node = p_lash->switches[sw]->node;
	char *name = p_lash->switches[sw]->p_sw->p_node->print_desc;
	int c = node->axes[port];

	p += sprintf(p, "%s[%d] = ", name, port);
	if (c)
		p += sprintf(p, "%s%c -> ", ((c - 1) & 1) ? "-" : "+", 'X' + (c - 1)/2);
	else
		p += sprintf(p, "N/A -> ");
	p += sprintf(p, "%s\n",
		     p_lash->switches[node->links[port]->switch_id]->p_sw->p_node->print_desc);
}