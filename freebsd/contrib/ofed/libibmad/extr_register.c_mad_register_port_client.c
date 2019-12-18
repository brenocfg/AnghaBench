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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int) ; 
 int mgmt_class_vers (int) ; 
 int umad_register (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mad_register_port_client(int port_id, int mgmt, uint8_t rmpp_version)
{
	int vers, agent;

	if ((vers = mgmt_class_vers(mgmt)) <= 0) {
		DEBUG("Unknown class %d mgmt_class", mgmt);
		return -1;
	}

	agent = umad_register(port_id, mgmt, vers, rmpp_version, 0);
	if (agent < 0)
		DEBUG("Can't register agent for class %d", mgmt);

	return agent;
}