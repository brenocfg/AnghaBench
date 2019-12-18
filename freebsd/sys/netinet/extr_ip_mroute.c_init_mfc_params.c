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
struct mfcctl2 {int /*<<< orphan*/  mfcc_mcastgrp; int /*<<< orphan*/  mfcc_origin; } ;
struct mfc {int /*<<< orphan*/  mfc_last_assert; scalar_t__ mfc_wrong_if; scalar_t__ mfc_byte_cnt; scalar_t__ mfc_pkt_cnt; int /*<<< orphan*/  mfc_mcastgrp; int /*<<< orphan*/  mfc_origin; } ;

/* Variables and functions */
 int /*<<< orphan*/  timevalclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_mfc_params (struct mfc*,struct mfcctl2*) ; 

__attribute__((used)) static void
init_mfc_params(struct mfc *rt, struct mfcctl2 *mfccp)
{
    rt->mfc_origin     = mfccp->mfcc_origin;
    rt->mfc_mcastgrp   = mfccp->mfcc_mcastgrp;

    update_mfc_params(rt, mfccp);

    /* initialize pkt counters per src-grp */
    rt->mfc_pkt_cnt    = 0;
    rt->mfc_byte_cnt   = 0;
    rt->mfc_wrong_if   = 0;
    timevalclear(&rt->mfc_last_assert);
}