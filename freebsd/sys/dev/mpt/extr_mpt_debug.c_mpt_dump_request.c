#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int RequestFrameSize; } ;
struct mpt_softc {TYPE_1__ ioc_facts; } ;
struct TYPE_5__ {scalar_t__ req_pbuf; int /*<<< orphan*/  index; int /*<<< orphan*/ * req_vbuf; } ;
typedef  TYPE_2__ request_t ;

/* Variables and functions */
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 
 int /*<<< orphan*/  mpt_prtc (struct mpt_softc*,char*,...) ; 

void
mpt_dump_request(struct mpt_softc *mpt, request_t *req)
{
        uint32_t *pReq = req->req_vbuf;
	int o;

	mpt_prt(mpt, "Send Request %d (%jx):",
	    req->index, (uintmax_t) req->req_pbuf);
	for (o = 0; o < mpt->ioc_facts.RequestFrameSize; o++) {
		if ((o & 0x7) == 0) {
			mpt_prtc(mpt, "\n");
			mpt_prt(mpt, " ");
		}
		mpt_prtc(mpt, " %08x", pReq[o]);
	}
	mpt_prtc(mpt, "\n");
}