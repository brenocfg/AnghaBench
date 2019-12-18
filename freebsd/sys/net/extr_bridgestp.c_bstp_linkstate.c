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
struct bstp_state {int dummy; } ;
struct bstp_port {int /*<<< orphan*/  bp_active; struct bstp_state* bp_bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  bstp_ifupdstatus (struct bstp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_update_state (struct bstp_state*,struct bstp_port*) ; 

void
bstp_linkstate(struct bstp_port *bp)
{
	struct bstp_state *bs = bp->bp_bs;

	if (!bp->bp_active)
		return;

	bstp_ifupdstatus(bp, 0);
	BSTP_LOCK(bs);
	bstp_update_state(bs, bp);
	BSTP_UNLOCK(bs);
}