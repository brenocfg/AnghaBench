#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; int /*<<< orphan*/  index; int /*<<< orphan*/  serno; } ;
typedef  TYPE_1__ request_t ;

/* Variables and functions */
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_tgt_dump_tgt_state (struct mpt_softc*,TYPE_1__*) ; 

__attribute__((used)) static void
mpt_tgt_dump_req_state(struct mpt_softc *mpt, request_t *req)
{

	mpt_prt(mpt, "req %p:%u index %u (%x) state %x\n", req, req->serno,
	    req->index, req->index, req->state);
	mpt_tgt_dump_tgt_state(mpt, req);
}