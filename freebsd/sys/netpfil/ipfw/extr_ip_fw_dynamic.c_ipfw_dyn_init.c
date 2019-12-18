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
struct ip_fw_chain {int dummy; } ;
struct dyn_parent {int dummy; } ;
struct dyn_ipv6_state {int dummy; } ;
struct dyn_ipv4_state {int dummy; } ;
struct dyn_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DYN_EXPIRED_LOCK_INIT () ; 
 int /*<<< orphan*/  IPFW_ADD_OBJ_REWRITER (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 scalar_t__ V_curr_dyn_buckets ; 
 int V_dyn_ack_lifetime ; 
 int /*<<< orphan*/ * V_dyn_bucket_lock ; 
 int V_dyn_buckets_max ; 
 void* V_dyn_data_zone ; 
 int /*<<< orphan*/  V_dyn_expired_ipv4 ; 
 int /*<<< orphan*/  V_dyn_expired_ipv6 ; 
 int V_dyn_fin_lifetime ; 
 int /*<<< orphan*/  V_dyn_hashseed ; 
 int /*<<< orphan*/ * V_dyn_ipv4 ; 
 int /*<<< orphan*/ * V_dyn_ipv4_parent ; 
 void* V_dyn_ipv4_zone ; 
 int /*<<< orphan*/ * V_dyn_ipv6 ; 
 int /*<<< orphan*/ * V_dyn_ipv6_parent ; 
 void* V_dyn_ipv6_zone ; 
 int V_dyn_keepalive ; 
 int V_dyn_keepalive_interval ; 
 int /*<<< orphan*/  V_dyn_keepalive_last ; 
 int V_dyn_keepalive_period ; 
 int V_dyn_max ; 
 int V_dyn_parent_max ; 
 void* V_dyn_parent_zone ; 
 int V_dyn_rst_lifetime ; 
 int V_dyn_short_lifetime ; 
 int V_dyn_syn_lifetime ; 
 int /*<<< orphan*/  V_dyn_timeout ; 
 int V_dyn_udp_lifetime ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  dyn_grow_hashtable (struct ip_fw_chain*,int) ; 
 int /*<<< orphan*/  dyn_hp_cache ; 
 int /*<<< orphan*/  dyn_opcodes ; 
 int /*<<< orphan*/  dyn_tick ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  time_uptime ; 
 void* uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_max (void*,int) ; 

void
ipfw_dyn_init(struct ip_fw_chain *chain)
{

#ifdef IPFIREWALL_JENKINSHASH
	V_dyn_hashseed = arc4random();
#endif
	V_dyn_max = 16384;		/* max # of states */
	V_dyn_parent_max = 4096;	/* max # of parent states */
	V_dyn_buckets_max = 8192;	/* must be power of 2 */

	V_dyn_ack_lifetime = 300;
	V_dyn_syn_lifetime = 20;
	V_dyn_fin_lifetime = 1;
	V_dyn_rst_lifetime = 1;
	V_dyn_udp_lifetime = 10;
	V_dyn_short_lifetime = 5;

	V_dyn_keepalive_interval = 20;
	V_dyn_keepalive_period = 5;
	V_dyn_keepalive = 1;		/* send keepalives */
	V_dyn_keepalive_last = time_uptime;

	V_dyn_data_zone = uma_zcreate("IPFW dynamic states data",
	    sizeof(struct dyn_data), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);
	uma_zone_set_max(V_dyn_data_zone, V_dyn_max);

	V_dyn_parent_zone = uma_zcreate("IPFW parent dynamic states",
	    sizeof(struct dyn_parent), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);
	uma_zone_set_max(V_dyn_parent_zone, V_dyn_parent_max);

	SLIST_INIT(&V_dyn_expired_ipv4);
	V_dyn_ipv4 = NULL;
	V_dyn_ipv4_parent = NULL;
	V_dyn_ipv4_zone = uma_zcreate("IPFW IPv4 dynamic states",
	    sizeof(struct dyn_ipv4_state), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);

#ifdef INET6
	SLIST_INIT(&V_dyn_expired_ipv6);
	V_dyn_ipv6 = NULL;
	V_dyn_ipv6_parent = NULL;
	V_dyn_ipv6_zone = uma_zcreate("IPFW IPv6 dynamic states",
	    sizeof(struct dyn_ipv6_state), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);
#endif

	/* Initialize buckets. */
	V_curr_dyn_buckets = 0;
	V_dyn_bucket_lock = NULL;
	dyn_grow_hashtable(chain, 256);

	if (IS_DEFAULT_VNET(curvnet))
		dyn_hp_cache = malloc(mp_ncpus * sizeof(void *), M_IPFW,
		    M_WAITOK | M_ZERO);

	DYN_EXPIRED_LOCK_INIT();
	callout_init(&V_dyn_timeout, 1);
	callout_reset(&V_dyn_timeout, hz, dyn_tick, curvnet);
	IPFW_ADD_OBJ_REWRITER(IS_DEFAULT_VNET(curvnet), dyn_opcodes);
}