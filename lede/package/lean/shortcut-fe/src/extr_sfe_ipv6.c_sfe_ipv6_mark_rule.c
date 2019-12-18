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
struct sfe_ipv6_connection {scalar_t__ mark; } ;
struct sfe_ipv6 {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip6; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip6; } ;
struct sfe_connection_mark {scalar_t__ mark; int /*<<< orphan*/  dest_port; TYPE_2__ dest_ip; int /*<<< orphan*/  src_port; TYPE_1__ src_ip; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TRACE (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sfe_ipv6 __si6 ; 
 struct sfe_ipv6_connection* sfe_ipv6_find_connection (struct sfe_ipv6*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void sfe_ipv6_mark_rule(struct sfe_connection_mark *mark)
{
	struct sfe_ipv6 *si = &__si6;
	struct sfe_ipv6_connection *c;

	spin_lock_bh(&si->lock);
	c = sfe_ipv6_find_connection(si, mark->protocol,
				     mark->src_ip.ip6, mark->src_port,
				     mark->dest_ip.ip6, mark->dest_port);
	if (c) {
		WARN_ON((0 != c->mark) && (0 == mark->mark));
		c->mark = mark->mark;
	}
	spin_unlock_bh(&si->lock);

	if (c) {
		DEBUG_TRACE("Matching connection found for mark, "
			    "setting from %08x to %08x\n",
			    c->mark, mark->mark);
	}
}