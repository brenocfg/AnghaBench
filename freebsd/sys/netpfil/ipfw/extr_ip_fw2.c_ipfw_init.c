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
 scalar_t__ IPFW_TABLES_MAX ; 
 scalar_t__ V_fw_verbose ; 
 int V_verbose_limit ; 
 scalar_t__ default_fw_tables ; 
 scalar_t__ default_to_accept ; 
 int /*<<< orphan*/  ipfw_iface_init () ; 
 int /*<<< orphan*/  ipfw_init_obj_rewriter () ; 
 int /*<<< orphan*/  ipfw_init_sopt_handler () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
ipfw_init(void)
{
	int error = 0;

	/*
 	 * Only print out this stuff the first time around,
	 * when called from the sysinit code.
	 */
	printf("ipfw2 "
#ifdef INET6
		"(+ipv6) "
#endif
		"initialized, divert %s, nat %s, "
		"default to %s, logging ",
#ifdef IPDIVERT
		"enabled",
#else
		"loadable",
#endif
#ifdef IPFIREWALL_NAT
		"enabled",
#else
		"loadable",
#endif
		default_to_accept ? "accept" : "deny");

	/*
	 * Note: V_xxx variables can be accessed here but the vnet specific
	 * initializer may not have been called yet for the VIMAGE case.
	 * Tuneables will have been processed. We will print out values for
	 * the default vnet. 
	 * XXX This should all be rationalized AFTER 8.0
	 */
	if (V_fw_verbose == 0)
		printf("disabled\n");
	else if (V_verbose_limit == 0)
		printf("unlimited\n");
	else
		printf("limited to %d packets/entry by default\n",
		    V_verbose_limit);

	/* Check user-supplied table count for validness */
	if (default_fw_tables > IPFW_TABLES_MAX)
	  default_fw_tables = IPFW_TABLES_MAX;

	ipfw_init_sopt_handler();
	ipfw_init_obj_rewriter();
	ipfw_iface_init();
	return (error);
}