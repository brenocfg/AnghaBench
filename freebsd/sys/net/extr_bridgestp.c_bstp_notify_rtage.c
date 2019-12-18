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
struct bstp_state {int /*<<< orphan*/  (* bs_rtage_cb ) (int /*<<< orphan*/ ,int) ;} ;
struct bstp_port {int bp_protover; int bp_desg_fdelay; int bp_active; scalar_t__ bp_fdbflush; int /*<<< orphan*/  bp_ifp; struct bstp_state* bp_bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
#define  BSTP_PROTO_RSTP 129 
#define  BSTP_PROTO_STP 128 
 int BSTP_TICK_VAL ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bstp_notify_rtage(void *arg, int pending)
{
	struct bstp_port *bp = (struct bstp_port *)arg;
	struct bstp_state *bs = bp->bp_bs;
	int age = 0;

	BSTP_LOCK(bs);
	switch (bp->bp_protover) {
		case BSTP_PROTO_STP:
			/* convert to seconds */
			age = bp->bp_desg_fdelay / BSTP_TICK_VAL;
			break;

		case BSTP_PROTO_RSTP:
			age = 0;
			break;
	}
	BSTP_UNLOCK(bs);

	if (bp->bp_active == 1 && bs->bs_rtage_cb != NULL)
		(*bs->bs_rtage_cb)(bp->bp_ifp, age);

	/* flush is complete */
	BSTP_LOCK(bs);
	bp->bp_fdbflush = 0;
	BSTP_UNLOCK(bs);
}