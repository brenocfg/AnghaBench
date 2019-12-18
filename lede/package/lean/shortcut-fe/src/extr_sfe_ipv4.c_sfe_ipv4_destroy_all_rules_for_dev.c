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
struct sfe_ipv4_connection {struct net_device* reply_dev; struct net_device* original_dev; struct sfe_ipv4_connection* all_connections_next; } ;
struct sfe_ipv4 {int /*<<< orphan*/  lock; struct sfe_ipv4_connection* all_connections_head; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFE_SYNC_REASON_DESTROY ; 
 struct sfe_ipv4 __si ; 
 int /*<<< orphan*/  sfe_ipv4_flush_sfe_ipv4_connection (struct sfe_ipv4*,struct sfe_ipv4_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfe_ipv4_remove_sfe_ipv4_connection (struct sfe_ipv4*,struct sfe_ipv4_connection*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void sfe_ipv4_destroy_all_rules_for_dev(struct net_device *dev)
{
	struct sfe_ipv4 *si = &__si;
	struct sfe_ipv4_connection *c;

another_round:
	spin_lock_bh(&si->lock);

	for (c = si->all_connections_head; c; c = c->all_connections_next) {
		/*
		 * Does this connection relate to the device we are destroying?
		 */
		if (!dev
		    || (dev == c->original_dev)
		    || (dev == c->reply_dev)) {
			break;
		}
	}

	if (c) {
		sfe_ipv4_remove_sfe_ipv4_connection(si, c);
	}

	spin_unlock_bh(&si->lock);

	if (c) {
		sfe_ipv4_flush_sfe_ipv4_connection(si, c, SFE_SYNC_REASON_DESTROY);
		goto another_round;
	}
}