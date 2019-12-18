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
typedef  int uint32_t ;

/* Variables and functions */
#define  FC_ADDR_CONTROLLER 130 
#define  FC_ADDR_FABRIC 129 
 int FC_ADDR_GET_DOMAIN_CTRL (int) ; 
 int /*<<< orphan*/  FC_ADDR_IS_DOMAIN_CTRL (int) ; 
#define  FC_ADDR_NAMESERVER 128 
 int /*<<< orphan*/  ocs_snprintf (char*,int,char*,...) ; 

void
ocs_node_fcid_display(uint32_t fc_id, char *buffer, uint32_t buffer_length)
{
	switch (fc_id) {
	case FC_ADDR_FABRIC:
		ocs_snprintf(buffer, buffer_length, "fabric");
		break;
	case FC_ADDR_CONTROLLER:
		ocs_snprintf(buffer, buffer_length, "fabctl");
		break;
	case FC_ADDR_NAMESERVER:
		ocs_snprintf(buffer, buffer_length, "nserve");
		break;
	default:
		if (FC_ADDR_IS_DOMAIN_CTRL(fc_id)) {
			ocs_snprintf(buffer, buffer_length, "dctl%02x",
				FC_ADDR_GET_DOMAIN_CTRL(fc_id));
		} else {
			ocs_snprintf(buffer, buffer_length, "%06x", fc_id);
		}
		break;
	}

}