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
struct ibmad_port {int* class_agents; } ;

/* Variables and functions */
 int MAX_CLASS ; 

int mad_rpc_class_agent(struct ibmad_port *port, int class)
{
	if (class < 1 || class >= MAX_CLASS)
		return -1;
	return port->class_agents[class];
}