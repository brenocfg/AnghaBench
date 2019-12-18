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
struct flow_offload {scalar_t__ timeout; } ;
struct fe_priv {int /*<<< orphan*/ * foe_flow_table; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 struct flow_offload* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void mtk_offload_keepalive(struct fe_priv *eth, unsigned int hash)
{
	struct flow_offload *flow;

	rcu_read_lock();
	flow = rcu_dereference(eth->foe_flow_table[hash]);
	if (flow)
		flow->timeout = jiffies + 30 * HZ;
	rcu_read_unlock();
}