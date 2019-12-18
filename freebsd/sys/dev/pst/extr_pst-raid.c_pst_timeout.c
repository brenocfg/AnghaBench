#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pst_request {int mfa; TYPE_1__* psc; TYPE_4__* bp; } ;
struct TYPE_7__ {int bio_cmd; } ;
struct TYPE_6__ {int /*<<< orphan*/  outstanding; int /*<<< orphan*/  mtx; } ;
struct TYPE_5__ {TYPE_2__* iop; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  biofinish (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iop_free_mfa (TYPE_2__*,int) ; 
 int iop_get_mfa (TYPE_2__*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ pst_rw (struct pst_request*) ; 

__attribute__((used)) static void
pst_timeout(void *arg)
{
    struct pst_request *request;

    request = arg;
    printf("pst: timeout mfa=0x%08x cmd=0x%02x\n",
	   request->mfa, request->bp->bio_cmd);
    mtx_assert(&request->psc->iop->mtx, MA_OWNED);
    iop_free_mfa(request->psc->iop, request->mfa);
    if ((request->mfa = iop_get_mfa(request->psc->iop)) == 0xffffffff) {
	printf("pst: timeout no mfa possible\n");
	biofinish(request->bp, NULL, EIO);
	request->psc->iop->outstanding--;
	return;
    }
    if (pst_rw(request)) {
	iop_free_mfa(request->psc->iop, request->mfa);
	biofinish(request->bp, NULL, EIO);
	request->psc->iop->outstanding--;
    }
}