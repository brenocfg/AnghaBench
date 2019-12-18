#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ibmad_port {int dummy; } ;
typedef  int /*<<< orphan*/  ibnd_node_t ;
typedef  int /*<<< orphan*/  ibnd_fabric_t ;

/* Variables and functions */
 int /*<<< orphan*/  dump_multicast_tables (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibmad_port*) ; 
 int /*<<< orphan*/  dump_unicast_tables (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibmad_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  endlid ; 
 scalar_t__ multicast ; 
 int /*<<< orphan*/  startlid ; 

void dump_node(ibnd_node_t *node, struct ibmad_port *mad_port,
		ibnd_fabric_t *fabric)
{
	if (multicast)
		dump_multicast_tables(node, startlid, endlid, mad_port);
	else
		dump_unicast_tables(node, startlid, endlid,
						mad_port, fabric);
}