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
typedef  int /*<<< orphan*/  uint8_t ;
struct ibmad_port {int* class_agents; } ;

/* Variables and functions */
 int mad_register_port_client (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_rpc_portid (struct ibmad_port*) ; 

int mad_register_client_via(int mgmt, uint8_t rmpp_version,
			    struct ibmad_port *srcport)
{
	int agent;

	if (!srcport)
		return -1;

	agent = mad_register_port_client(mad_rpc_portid(srcport), mgmt,
					 rmpp_version);
	if (agent < 0)
		return agent;

	srcport->class_agents[mgmt] = agent;
	return 0;
}