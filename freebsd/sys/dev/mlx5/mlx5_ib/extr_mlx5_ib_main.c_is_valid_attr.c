#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ether_type; } ;
struct TYPE_4__ {scalar_t__ ether_type; } ;
struct TYPE_6__ {TYPE_2__ val; TYPE_1__ mask; } ;
union ib_flow_spec {scalar_t__ type; int size; TYPE_3__ eth; } ;
struct ib_flow_attr {unsigned int num_of_specs; } ;

/* Variables and functions */
 int ETH_P_IP ; 
 scalar_t__ IB_FLOW_SPEC_ETH ; 
 scalar_t__ IB_FLOW_SPEC_IPV4 ; 
 scalar_t__ htons (int) ; 

__attribute__((used)) static bool is_valid_attr(const struct ib_flow_attr *flow_attr)
{
	union ib_flow_spec *ib_spec = (union ib_flow_spec *)(flow_attr + 1);
	bool has_ipv4_spec = false;
	bool eth_type_ipv4 = true;
	unsigned int spec_index;

	/* Validate that ethertype is correct */
	for (spec_index = 0; spec_index < flow_attr->num_of_specs; spec_index++) {
		if (ib_spec->type == IB_FLOW_SPEC_ETH &&
		    ib_spec->eth.mask.ether_type) {
			if (!((ib_spec->eth.mask.ether_type == htons(0xffff)) &&
			      ib_spec->eth.val.ether_type == htons(ETH_P_IP)))
				eth_type_ipv4 = false;
		} else if (ib_spec->type == IB_FLOW_SPEC_IPV4) {
			has_ipv4_spec = true;
		}
		ib_spec = (void *)ib_spec + ib_spec->size;
	}
	return !has_ipv4_spec || eth_type_ipv4;
}