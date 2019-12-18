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
struct ip_fw_chain {int n_rules; int /*<<< orphan*/ * map; } ;
struct ip_fw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_LOCK_DESTROY (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 scalar_t__ IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/ * V_ip_fw_ctl_ptr ; 
 scalar_t__ V_ipfw_vnet_ready ; 
 struct ip_fw_chain V_layer3_chain ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_bpf_uninit (int) ; 
 int /*<<< orphan*/  ipfw_destroy_counters () ; 
 int /*<<< orphan*/  ipfw_destroy_skipto_cache (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  ipfw_destroy_srv (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  ipfw_destroy_tables (struct ip_fw_chain*,int) ; 
 int /*<<< orphan*/  ipfw_detach_hooks () ; 
 int /*<<< orphan*/  ipfw_dyn_uninit (int) ; 
 int /*<<< orphan*/  ipfw_eaction_uninit (struct ip_fw_chain*,int) ; 
 int /*<<< orphan*/  ipfw_reap_add (struct ip_fw_chain*,struct ip_fw**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_reap_rules (struct ip_fw*) ; 
 int /*<<< orphan*/  vnet_ipfw_iface_destroy (struct ip_fw_chain*) ; 

__attribute__((used)) static int
vnet_ipfw_uninit(const void *unused)
{
	struct ip_fw *reap;
	struct ip_fw_chain *chain = &V_layer3_chain;
	int i, last;

	V_ipfw_vnet_ready = 0; /* tell new callers to go away */
	/*
	 * disconnect from ipv4, ipv6, layer2 and sockopt.
	 * Then grab, release and grab again the WLOCK so we make
	 * sure the update is propagated and nobody will be in.
	 */
	ipfw_detach_hooks();
	V_ip_fw_ctl_ptr = NULL;

	last = IS_DEFAULT_VNET(curvnet) ? 1 : 0;

	IPFW_UH_WLOCK(chain);
	IPFW_UH_WUNLOCK(chain);

	ipfw_dyn_uninit(0);	/* run the callout_drain */

	IPFW_UH_WLOCK(chain);

	reap = NULL;
	IPFW_WLOCK(chain);
	for (i = 0; i < chain->n_rules; i++)
		ipfw_reap_add(chain, &reap, chain->map[i]);
	free(chain->map, M_IPFW);
#ifdef LINEAR_SKIPTO
	ipfw_destroy_skipto_cache(chain);
#endif
	IPFW_WUNLOCK(chain);
	IPFW_UH_WUNLOCK(chain);
	ipfw_destroy_tables(chain, last);
	ipfw_eaction_uninit(chain, last);
	if (reap != NULL)
		ipfw_reap_rules(reap);
	vnet_ipfw_iface_destroy(chain);
	ipfw_destroy_srv(chain);
	IPFW_LOCK_DESTROY(chain);
	ipfw_dyn_uninit(1);	/* free the remaining parts */
	ipfw_destroy_counters();
	ipfw_bpf_uninit(last);
	return (0);
}