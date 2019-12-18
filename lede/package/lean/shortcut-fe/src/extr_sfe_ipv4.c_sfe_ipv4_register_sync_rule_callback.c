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
struct sfe_ipv4 {int /*<<< orphan*/  lock; int /*<<< orphan*/  sync_rule_callback; } ;
typedef  int /*<<< orphan*/  sfe_sync_rule_callback_t ;

/* Variables and functions */
 struct sfe_ipv4 __si ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void sfe_ipv4_register_sync_rule_callback(sfe_sync_rule_callback_t sync_rule_callback)
{
	struct sfe_ipv4 *si = &__si;

	spin_lock_bh(&si->lock);
	rcu_assign_pointer(si->sync_rule_callback, sync_rule_callback);
	spin_unlock_bh(&si->lock);
}