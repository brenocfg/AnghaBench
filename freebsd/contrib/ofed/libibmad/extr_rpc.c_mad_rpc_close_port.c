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
struct ibmad_port {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibmad_port*) ; 
 int /*<<< orphan*/  umad_close_port (int /*<<< orphan*/ ) ; 

void mad_rpc_close_port(struct ibmad_port *port)
{
	umad_close_port(port->port_id);
	free(port);
}