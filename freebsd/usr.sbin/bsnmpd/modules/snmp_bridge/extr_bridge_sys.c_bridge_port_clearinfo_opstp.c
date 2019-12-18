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
struct bridge_port {scalar_t__ enable; scalar_t__ fwd_trans; int /*<<< orphan*/  design_port; int /*<<< orphan*/  design_bridge; int /*<<< orphan*/  design_root; scalar_t__ design_cost; } ;
typedef  int /*<<< orphan*/  port_id ;
typedef  int /*<<< orphan*/  bridge_id ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dot1dStpPortEnable_disabled ; 
 scalar_t__ dot1dStpPortEnable_enabled ; 

__attribute__((used)) static void
bridge_port_clearinfo_opstp(struct bridge_port *bp)
{
	if (bp->enable == dot1dStpPortEnable_enabled) {
		bp->design_cost = 0;
		bzero(&(bp->design_root), sizeof(bridge_id));
		bzero(&(bp->design_bridge), sizeof(bridge_id));
		bzero(&(bp->design_port), sizeof(port_id));
		bp->fwd_trans = 0;
	}

	bp->enable = dot1dStpPortEnable_disabled;
}