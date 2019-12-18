#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ib_portid_t ;
struct TYPE_13__ {int dist; struct TYPE_13__* dnext; int /*<<< orphan*/  path; } ;
struct TYPE_12__ {scalar_t__ portguid; int /*<<< orphan*/  lid; int /*<<< orphan*/  portnum; } ;
typedef  TYPE_1__ Port ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE (char*,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_endnode (int /*<<< orphan*/ ,char*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ibverbose ; 
 scalar_t__ insert_node (TYPE_2__*) ; 
 int /*<<< orphan*/  link_port (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__** nodesdist ; 
 scalar_t__ target_portguid ; 

__attribute__((used)) static int new_node(Node * node, Port * port, ib_portid_t * path, int dist)
{
	if (port->portguid == target_portguid) {
		node->dist = -1;	/* tag as target */
		link_port(port, node);
		dump_endnode(ibverbose, "found target", node, port);
		return 1;	/* found; */
	}

	/* BFS search start with my self */
	if (insert_node(node) < 0)
		return -1;	/* known switch */

	VERBOSE("insert dist %d node %p port %d lid %d", dist, node,
		port->portnum, port->lid);

	link_port(port, node);

	node->dist = dist;
	node->path = *path;
	node->dnext = nodesdist[dist];
	nodesdist[dist] = node;

	return 0;
}