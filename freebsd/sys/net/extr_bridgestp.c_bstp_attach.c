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
struct bstp_state {int /*<<< orphan*/  bs_last_tc_time; int /*<<< orphan*/  bs_vnet; int /*<<< orphan*/  bs_rtage_cb; int /*<<< orphan*/  bs_state_cb; int /*<<< orphan*/  bs_protover; int /*<<< orphan*/  bs_txholdcount; int /*<<< orphan*/  bs_migration_delay; int /*<<< orphan*/  bs_hold_time; int /*<<< orphan*/  bs_bridge_priority; int /*<<< orphan*/  bs_bridge_fdelay; int /*<<< orphan*/  bs_bridge_htime; int /*<<< orphan*/  bs_bridge_max_age; int /*<<< orphan*/  bs_bplist; int /*<<< orphan*/  bs_mtx; int /*<<< orphan*/  bs_bstpcallout; } ;
struct bstp_cb_ops {int /*<<< orphan*/  bcb_rtage; int /*<<< orphan*/  bcb_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_DEFAULT_BRIDGE_PRIORITY ; 
 int /*<<< orphan*/  BSTP_DEFAULT_FORWARD_DELAY ; 
 int /*<<< orphan*/  BSTP_DEFAULT_HELLO_TIME ; 
 int /*<<< orphan*/  BSTP_DEFAULT_HOLD_COUNT ; 
 int /*<<< orphan*/  BSTP_DEFAULT_HOLD_TIME ; 
 int /*<<< orphan*/  BSTP_DEFAULT_MAX_AGE ; 
 int /*<<< orphan*/  BSTP_DEFAULT_MIGRATE_DELAY ; 
 int /*<<< orphan*/  BSTP_LOCK_INIT (struct bstp_state*) ; 
 int /*<<< orphan*/  BSTP_PROTO_RSTP ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct bstp_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_list ; 
 int /*<<< orphan*/  bstp_list ; 
 int /*<<< orphan*/  bstp_list_mtx ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  getmicrotime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
bstp_attach(struct bstp_state *bs, struct bstp_cb_ops *cb)
{
	BSTP_LOCK_INIT(bs);
	callout_init_mtx(&bs->bs_bstpcallout, &bs->bs_mtx, 0);
	LIST_INIT(&bs->bs_bplist);

	bs->bs_bridge_max_age = BSTP_DEFAULT_MAX_AGE;
	bs->bs_bridge_htime = BSTP_DEFAULT_HELLO_TIME;
	bs->bs_bridge_fdelay = BSTP_DEFAULT_FORWARD_DELAY;
	bs->bs_bridge_priority = BSTP_DEFAULT_BRIDGE_PRIORITY;
	bs->bs_hold_time = BSTP_DEFAULT_HOLD_TIME;
	bs->bs_migration_delay = BSTP_DEFAULT_MIGRATE_DELAY;
	bs->bs_txholdcount = BSTP_DEFAULT_HOLD_COUNT;
	bs->bs_protover = BSTP_PROTO_RSTP;
	bs->bs_state_cb = cb->bcb_state;
	bs->bs_rtage_cb = cb->bcb_rtage;
	bs->bs_vnet = curvnet;

	getmicrotime(&bs->bs_last_tc_time);

	mtx_lock(&bstp_list_mtx);
	LIST_INSERT_HEAD(&bstp_list, bs, bs_list);
	mtx_unlock(&bstp_list_mtx);
}