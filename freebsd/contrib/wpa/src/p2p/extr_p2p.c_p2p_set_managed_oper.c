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
struct p2p_data {int /*<<< orphan*/  dev_capab; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_DEV_CAPAB_INFRA_MANAGED ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 

void p2p_set_managed_oper(struct p2p_data *p2p, int enabled)
{
	if (enabled) {
		p2p_dbg(p2p, "Managed P2P Device operations enabled");
		p2p->dev_capab |= P2P_DEV_CAPAB_INFRA_MANAGED;
	} else {
		p2p_dbg(p2p, "Managed P2P Device operations disabled");
		p2p->dev_capab &= ~P2P_DEV_CAPAB_INFRA_MANAGED;
	}
}