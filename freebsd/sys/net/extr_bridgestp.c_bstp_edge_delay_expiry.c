#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bstp_state {int dummy; } ;
struct bstp_port {int bp_flags; scalar_t__ bp_protover; scalar_t__ bp_role; int bp_operedge; TYPE_1__* bp_ifp; scalar_t__ bp_proposing; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int BSTP_PORT_AUTOEDGE ; 
 scalar_t__ BSTP_PROTO_RSTP ; 
 scalar_t__ BSTP_ROLE_DESIGNATED ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bstp_edge_delay_expiry(struct bstp_state *bs, struct bstp_port *bp)
{
	if ((bp->bp_flags & BSTP_PORT_AUTOEDGE) &&
	    bp->bp_protover == BSTP_PROTO_RSTP && bp->bp_proposing &&
	    bp->bp_role == BSTP_ROLE_DESIGNATED) {
		bp->bp_operedge = 1;
		DPRINTF("%s -> edge port\n", bp->bp_ifp->if_xname);
	}
}