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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPFW_ADD_SOPT_HANDLER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifaddr_change ; 
 int /*<<< orphan*/  ifaddr_event ; 
 int /*<<< orphan*/  ifaddr_event_tag ; 
 int /*<<< orphan*/  ipfw_nat ; 
 int /*<<< orphan*/  ipfw_nat_cfg ; 
 int /*<<< orphan*/  ipfw_nat_cfg_ptr ; 
 int /*<<< orphan*/  ipfw_nat_del ; 
 int /*<<< orphan*/  ipfw_nat_del_ptr ; 
 int /*<<< orphan*/  ipfw_nat_get_cfg ; 
 int /*<<< orphan*/  ipfw_nat_get_cfg_ptr ; 
 int /*<<< orphan*/  ipfw_nat_get_log ; 
 int /*<<< orphan*/  ipfw_nat_get_log_ptr ; 
 int /*<<< orphan*/  ipfw_nat_ptr ; 
 int /*<<< orphan*/  lookup_nat ; 
 int /*<<< orphan*/  lookup_nat_ptr ; 
 int /*<<< orphan*/  scodes ; 

__attribute__((used)) static void
ipfw_nat_init(void)
{

	/* init ipfw hooks */
	ipfw_nat_ptr = ipfw_nat;
	lookup_nat_ptr = lookup_nat;
	ipfw_nat_cfg_ptr = ipfw_nat_cfg;
	ipfw_nat_del_ptr = ipfw_nat_del;
	ipfw_nat_get_cfg_ptr = ipfw_nat_get_cfg;
	ipfw_nat_get_log_ptr = ipfw_nat_get_log;
	IPFW_ADD_SOPT_HANDLER(1, scodes);

	ifaddr_event_tag = EVENTHANDLER_REGISTER(ifaddr_event, ifaddr_change,
	    NULL, EVENTHANDLER_PRI_ANY);
}