#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sfe_ipv6_connection {int dummy; } ;
struct sfe_ipv6 {int /*<<< orphan*/  lock; int /*<<< orphan*/  connection_destroy_misses; int /*<<< orphan*/  connection_destroy_requests; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip6; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip6; } ;
struct sfe_connection_destroy {int /*<<< orphan*/  dest_port; TYPE_2__ dest_ip; int /*<<< orphan*/  src_port; TYPE_1__ src_ip; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SFE_SYNC_REASON_DESTROY ; 
 struct sfe_ipv6 __si6 ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct sfe_ipv6_connection* sfe_ipv6_find_connection (struct sfe_ipv6*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfe_ipv6_flush_connection (struct sfe_ipv6*,struct sfe_ipv6_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfe_ipv6_remove_connection (struct sfe_ipv6*,struct sfe_ipv6_connection*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void sfe_ipv6_destroy_rule(struct sfe_connection_destroy *sid)
{
	struct sfe_ipv6 *si = &__si6;
	struct sfe_ipv6_connection *c;

	spin_lock_bh(&si->lock);
	si->connection_destroy_requests++;

	/*
	 * Check to see if we have a flow that matches the rule we're trying
	 * to destroy.  If there isn't then we can't destroy it.
	 */
	c = sfe_ipv6_find_connection(si, sid->protocol, sid->src_ip.ip6, sid->src_port,
				     sid->dest_ip.ip6, sid->dest_port);
	if (!c) {
		si->connection_destroy_misses++;
		spin_unlock_bh(&si->lock);

		DEBUG_TRACE("connection does not exist - p: %d, s: %pI6:%u, d: %pI6:%u\n",
			    sid->protocol, sid->src_ip.ip6, ntohs(sid->src_port),
			    sid->dest_ip.ip6, ntohs(sid->dest_port));
		return;
	}

	/*
	 * Remove our connection details from the hash tables.
	 */
	sfe_ipv6_remove_connection(si, c);
	spin_unlock_bh(&si->lock);

	sfe_ipv6_flush_connection(si, c, SFE_SYNC_REASON_DESTROY);

	DEBUG_INFO("connection destroyed - p: %d, s: %pI6:%u, d: %pI6:%u\n",
		   sid->protocol, sid->src_ip.ip6, ntohs(sid->src_port),
		   sid->dest_ip.ip6, ntohs(sid->dest_port));
}