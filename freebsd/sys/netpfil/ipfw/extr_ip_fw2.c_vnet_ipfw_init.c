#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ip_fw_chain {struct ip_fw* default_rule; struct ip_fw* map; int /*<<< orphan*/  nat; } ;
struct ip_fw {int cmd_len; TYPE_1__* cmd; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  IPFIREWALL_VERBOSE_LIMIT ; 
 int /*<<< orphan*/  IPFW_LOCK_INIT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_RULE_NOOPT ; 
 scalar_t__ IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  O_ACCEPT ; 
 int /*<<< orphan*/  O_DENY ; 
 int V_autoinc_step ; 
 int V_fw_deny_unknown_exthdrs ; 
 int /*<<< orphan*/  V_fw_tables_max ; 
 int V_fw_verbose ; 
 int /*<<< orphan*/  V_ip_fw_ctl_ptr ; 
 int V_ipfw_vnet_ready ; 
 struct ip_fw_chain V_layer3_chain ; 
 int /*<<< orphan*/  V_verbose_limit ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  default_fw_tables ; 
 scalar_t__ default_to_accept ; 
 int /*<<< orphan*/  free (struct ip_fw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_add_protected_rule (struct ip_fw_chain*,struct ip_fw*,int /*<<< orphan*/ ) ; 
 struct ip_fw* ipfw_alloc_rule (struct ip_fw_chain*,int) ; 
 int ipfw_attach_hooks () ; 
 int /*<<< orphan*/  ipfw_bpf_init (int) ; 
 int /*<<< orphan*/  ipfw_ctl3 ; 
 int /*<<< orphan*/  ipfw_dyn_init (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  ipfw_eaction_init (struct ip_fw_chain*,int) ; 
 int /*<<< orphan*/  ipfw_init_counters () ; 
 int /*<<< orphan*/  ipfw_init_skipto_cache (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  ipfw_init_srv (struct ip_fw_chain*) ; 
 int ipfw_init_tables (struct ip_fw_chain*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
vnet_ipfw_init(const void *unused)
{
	int error, first;
	struct ip_fw *rule = NULL;
	struct ip_fw_chain *chain;

	chain = &V_layer3_chain;

	first = IS_DEFAULT_VNET(curvnet) ? 1 : 0;

	/* First set up some values that are compile time options */
	V_autoinc_step = 100;	/* bounded to 1..1000 in add_rule() */
	V_fw_deny_unknown_exthdrs = 1;
#ifdef IPFIREWALL_VERBOSE
	V_fw_verbose = 1;
#endif
#ifdef IPFIREWALL_VERBOSE_LIMIT
	V_verbose_limit = IPFIREWALL_VERBOSE_LIMIT;
#endif
#ifdef IPFIREWALL_NAT
	LIST_INIT(&chain->nat);
#endif

	/* Init shared services hash table */
	ipfw_init_srv(chain);

	ipfw_init_counters();
	/* Set initial number of tables */
	V_fw_tables_max = default_fw_tables;
	error = ipfw_init_tables(chain, first);
	if (error) {
		printf("ipfw2: setting up tables failed\n");
		free(chain->map, M_IPFW);
		free(rule, M_IPFW);
		return (ENOSPC);
	}

	IPFW_LOCK_INIT(chain);

	/* fill and insert the default rule */
	rule = ipfw_alloc_rule(chain, sizeof(struct ip_fw));
	rule->flags |= IPFW_RULE_NOOPT;
	rule->cmd_len = 1;
	rule->cmd[0].len = 1;
	rule->cmd[0].opcode = default_to_accept ? O_ACCEPT : O_DENY;
	chain->default_rule = rule;
	ipfw_add_protected_rule(chain, rule, 0);

	ipfw_dyn_init(chain);
	ipfw_eaction_init(chain, first);
#ifdef LINEAR_SKIPTO
	ipfw_init_skipto_cache(chain);
#endif
	ipfw_bpf_init(first);

	/* First set up some values that are compile time options */
	V_ipfw_vnet_ready = 1;		/* Open for business */

	/*
	 * Hook the sockopt handler and pfil hooks for ipv4 and ipv6.
	 * Even if the latter two fail we still keep the module alive
	 * because the sockopt and layer2 paths are still useful.
	 * ipfw[6]_hook return 0 on success, ENOENT on failure,
	 * so we can ignore the exact return value and just set a flag.
	 *
	 * Note that V_fw[6]_enable are manipulated by a SYSCTL_PROC so
	 * changes in the underlying (per-vnet) variables trigger
	 * immediate hook()/unhook() calls.
	 * In layer2 we have the same behaviour, except that V_ether_ipfw
	 * is checked on each packet because there are no pfil hooks.
	 */
	V_ip_fw_ctl_ptr = ipfw_ctl3;
	error = ipfw_attach_hooks();
	return (error);
}