#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numports; int smalid; int smalmc; scalar_t__ smaenhsp0; int /*<<< orphan*/  nodedesc; int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ ibnd_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char*,char*,char*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* node_name (TYPE_1__*) ; 
 int /*<<< orphan*/  node_name_map ; 
 char* remap_node_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void out_switch_detail(ibnd_node_t * node, char *sw_prefix)
{
	char *nodename = NULL;

	nodename = remap_node_name(node_name_map, node->guid, node->nodedesc);

	fprintf(f, "%sSwitch\t%d %s\t\t# \"%s\" %s port 0 lid %d lmc %d",
		sw_prefix ? sw_prefix : "", node->numports, node_name(node),
		nodename, node->smaenhsp0 ? "enhanced" : "base",
		node->smalid, node->smalmc);

	free(nodename);
}