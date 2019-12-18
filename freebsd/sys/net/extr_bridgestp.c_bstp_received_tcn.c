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
struct bstp_tcn_unit {int dummy; } ;
struct bstp_state {int dummy; } ;
struct bstp_port {int bp_rcvdtcn; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstp_update_tc (struct bstp_port*) ; 

__attribute__((used)) static void
bstp_received_tcn(struct bstp_state *bs, struct bstp_port *bp,
    struct bstp_tcn_unit *tcn)
{
	bp->bp_rcvdtcn = 1;
	bstp_update_tc(bp);
}