#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  b_bytes; int /*<<< orphan*/  b_packets; struct timeval b_time; } ;
struct TYPE_7__ {int /*<<< orphan*/  b_bytes; int /*<<< orphan*/  b_packets; int /*<<< orphan*/  b_time; } ;
struct bw_upcall {int /*<<< orphan*/  bu_flags; TYPE_4__ bu_measured; TYPE_2__ bu_threshold; int /*<<< orphan*/  bu_dst; int /*<<< orphan*/  bu_src; } ;
struct TYPE_10__ {int /*<<< orphan*/  b_bytes; int /*<<< orphan*/  b_packets; } ;
struct TYPE_8__ {int /*<<< orphan*/  b_bytes; int /*<<< orphan*/  b_packets; int /*<<< orphan*/  b_time; } ;
struct bw_meter {int bm_flags; TYPE_5__ bm_measured; TYPE_3__ bm_threshold; TYPE_1__* bm_mfc; int /*<<< orphan*/  bm_start_time; } ;
struct TYPE_6__ {int /*<<< orphan*/  mfc_mcastgrp; int /*<<< orphan*/  mfc_origin; } ;

/* Variables and functions */
 int BW_METER_GEQ ; 
 int BW_METER_LEQ ; 
 int BW_METER_UNIT_BYTES ; 
 int BW_METER_UNIT_PACKETS ; 
 int /*<<< orphan*/  BW_TIMEVALDECR (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ BW_UPCALLS_MAX ; 
 int /*<<< orphan*/  BW_UPCALL_GEQ ; 
 int /*<<< orphan*/  BW_UPCALL_LEQ ; 
 int /*<<< orphan*/  BW_UPCALL_UNIT_BYTES ; 
 int /*<<< orphan*/  BW_UPCALL_UNIT_PACKETS ; 
 int /*<<< orphan*/  MFC_LOCK_ASSERT () ; 
 struct bw_upcall* V_bw_upcalls ; 
 scalar_t__ V_bw_upcalls_n ; 
 int /*<<< orphan*/  bw_upcalls_send () ; 

__attribute__((used)) static void
bw_meter_prepare_upcall(struct bw_meter *x, struct timeval *nowp)
{
    struct timeval delta;
    struct bw_upcall *u;

    MFC_LOCK_ASSERT();

    /*
     * Compute the measured time interval
     */
    delta = *nowp;
    BW_TIMEVALDECR(&delta, &x->bm_start_time);

    /*
     * If there are too many pending upcalls, deliver them now
     */
    if (V_bw_upcalls_n >= BW_UPCALLS_MAX)
	bw_upcalls_send();

    /*
     * Set the bw_upcall entry
     */
    u = &V_bw_upcalls[V_bw_upcalls_n++];
    u->bu_src = x->bm_mfc->mfc_origin;
    u->bu_dst = x->bm_mfc->mfc_mcastgrp;
    u->bu_threshold.b_time = x->bm_threshold.b_time;
    u->bu_threshold.b_packets = x->bm_threshold.b_packets;
    u->bu_threshold.b_bytes = x->bm_threshold.b_bytes;
    u->bu_measured.b_time = delta;
    u->bu_measured.b_packets = x->bm_measured.b_packets;
    u->bu_measured.b_bytes = x->bm_measured.b_bytes;
    u->bu_flags = 0;
    if (x->bm_flags & BW_METER_UNIT_PACKETS)
	u->bu_flags |= BW_UPCALL_UNIT_PACKETS;
    if (x->bm_flags & BW_METER_UNIT_BYTES)
	u->bu_flags |= BW_UPCALL_UNIT_BYTES;
    if (x->bm_flags & BW_METER_GEQ)
	u->bu_flags |= BW_UPCALL_GEQ;
    if (x->bm_flags & BW_METER_LEQ)
	u->bu_flags |= BW_UPCALL_LEQ;
}