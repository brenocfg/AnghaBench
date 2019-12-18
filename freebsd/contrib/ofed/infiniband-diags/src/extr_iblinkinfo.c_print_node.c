#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ ibnd_port_t ;
struct TYPE_8__ {int numports; TYPE_1__** ports; } ;
typedef  TYPE_2__ ibnd_node_t ;

/* Variables and functions */
 scalar_t__ IB_LINK_DOWN ; 
 int /*<<< orphan*/  IB_PORT_STATE_F ; 
 int /*<<< orphan*/  down_links_only ; 
 scalar_t__ mad_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_node_header (TYPE_2__*,int*,char*) ; 
 int /*<<< orphan*/  print_port (TYPE_2__*,TYPE_1__*,char*) ; 

void print_node(ibnd_node_t * node, void *user_data)
{
	int i = 0;
	int head_print = 0;
	char *out_prefix = (char *)user_data;

	for (i = 1; i <= node->numports; i++) {
		ibnd_port_t *port = node->ports[i];
		if (!port)
			continue;
		if (!down_links_only ||
		    mad_get_field(port->info, 0,
				  IB_PORT_STATE_F) == IB_LINK_DOWN) {
			print_node_header(node, &head_print, out_prefix);
			print_port(node, port, out_prefix);
		}
	}
}