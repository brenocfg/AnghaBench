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
typedef  int /*<<< orphan*/  uint16_t ;
struct ip_fw_chain {int dummy; } ;
typedef  enum ipfw_sets_cmd { ____Placeholder_ipfw_sets_cmd } ipfw_sets_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_TLV_NAT64STL_NAME ; 
 int ipfw_obj_manage_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nat64stl_manage_sets(struct ip_fw_chain *ch, uint16_t set, uint8_t new_set,
    enum ipfw_sets_cmd cmd)
{

	return (ipfw_obj_manage_sets(CHAIN_TO_SRV(ch), IPFW_TLV_NAT64STL_NAME,
	    set, new_set, cmd));
}