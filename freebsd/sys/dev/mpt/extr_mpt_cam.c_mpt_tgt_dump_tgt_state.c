#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  serno; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_8__ {int /*<<< orphan*/  state; int /*<<< orphan*/  itag; int /*<<< orphan*/  tag_id; int /*<<< orphan*/  nxfers; int /*<<< orphan*/  req; int /*<<< orphan*/  ccb; int /*<<< orphan*/  bytes_xfered; int /*<<< orphan*/  resid; int /*<<< orphan*/  reply_desc; } ;
typedef  TYPE_2__ mpt_tgt_state_t ;

/* Variables and functions */
 TYPE_2__* MPT_TGT_STATE (struct mpt_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mpt_tgt_dump_tgt_state(struct mpt_softc *mpt, request_t *req)
{
	mpt_tgt_state_t *tgt = MPT_TGT_STATE(mpt, req);

	mpt_prt(mpt, "req %p:%u tgt:rdesc 0x%x resid %u xfrd %u ccb %p treq %p "
	    "nx %d tag 0x%08x itag 0x%04x state=%d\n", req, req->serno,
	    tgt->reply_desc, tgt->resid, tgt->bytes_xfered, tgt->ccb,
	    tgt->req, tgt->nxfers, tgt->tag_id, tgt->itag, tgt->state);
}