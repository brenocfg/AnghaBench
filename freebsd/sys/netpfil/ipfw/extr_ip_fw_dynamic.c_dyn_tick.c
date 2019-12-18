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
struct vnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (struct vnet*) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (int /*<<< orphan*/ *) ; 
 int V_curr_dyn_buckets ; 
 int V_curr_max_length ; 
 int V_dyn_buckets_max ; 
 int V_dyn_count ; 
 scalar_t__ V_dyn_keepalive ; 
 scalar_t__ V_dyn_keepalive_last ; 
 scalar_t__ V_dyn_keepalive_period ; 
 int /*<<< orphan*/  V_dyn_timeout ; 
 int /*<<< orphan*/  V_layer3_chain ; 
 int /*<<< orphan*/  callout_reset_on (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_expire_states (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dyn_free_states (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dyn_grow_hashtable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dyn_send_keepalive_ipv4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dyn_send_keepalive_ipv6 (int /*<<< orphan*/ *) ; 
 int fls (int) ; 
 int /*<<< orphan*/  hz ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static void
dyn_tick(void *vnetx)
{
	uint32_t buckets;

	CURVNET_SET((struct vnet *)vnetx);
	/*
	 * First free states unlinked in previous passes.
	 */
	dyn_free_states(&V_layer3_chain);
	/*
	 * Now unlink others expired states.
	 * We use IPFW_UH_WLOCK to avoid concurrent call of
	 * dyn_expire_states(). It is the only function that does
	 * deletion of state entries from states lists.
	 */
	IPFW_UH_WLOCK(&V_layer3_chain);
	dyn_expire_states(&V_layer3_chain, NULL);
	IPFW_UH_WUNLOCK(&V_layer3_chain);
	/*
	 * Send keepalives if they are enabled and the time has come.
	 */
	if (V_dyn_keepalive != 0 &&
	    V_dyn_keepalive_last + V_dyn_keepalive_period <= time_uptime) {
		V_dyn_keepalive_last = time_uptime;
		dyn_send_keepalive_ipv4(&V_layer3_chain);
#ifdef INET6
		dyn_send_keepalive_ipv6(&V_layer3_chain);
#endif
	}
	/*
	 * Check if we need to resize the hash:
	 * if current number of states exceeds number of buckets in hash,
	 * and dyn_buckets_max permits to grow the number of buckets, then
	 * do it. Grow hash size to the minimum power of 2 which is bigger
	 * than current states count.
	 */
	if (V_curr_dyn_buckets < V_dyn_buckets_max &&
	    (V_curr_dyn_buckets < V_dyn_count / 2 || (
	    V_curr_dyn_buckets < V_dyn_count && V_curr_max_length > 8))) {
		buckets = 1 << fls(V_dyn_count);
		if (buckets > V_dyn_buckets_max)
			buckets = V_dyn_buckets_max;
		dyn_grow_hashtable(&V_layer3_chain, buckets);
	}

	callout_reset_on(&V_dyn_timeout, hz, dyn_tick, vnetx, 0);
	CURVNET_RESTORE();
}