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
struct bstp_state {int /*<<< orphan*/  (* bs_state_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct bstp_port {int bp_active; int /*<<< orphan*/  bp_state; int /*<<< orphan*/  bp_ifp; struct bstp_state* bp_bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bstp_notify_state(void *arg, int pending)
{
	struct bstp_port *bp = (struct bstp_port *)arg;
	struct bstp_state *bs = bp->bp_bs;

	if (bp->bp_active == 1 && bs->bs_state_cb != NULL)
		(*bs->bs_state_cb)(bp->bp_ifp, bp->bp_state);
}