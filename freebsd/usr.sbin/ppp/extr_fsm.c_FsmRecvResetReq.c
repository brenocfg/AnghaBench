#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct fsmheader {int /*<<< orphan*/  id; } ;
struct fsm {int /*<<< orphan*/  link; TYPE_1__* fn; } ;
struct TYPE_2__ {scalar_t__ (* RecvResetReq ) (struct fsm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_RESETACK ; 
 int /*<<< orphan*/  MB_CCPOUT ; 
 int /*<<< orphan*/  fsm_Output (struct fsm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_SequenceQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ stub1 (struct fsm*) ; 

__attribute__((used)) static void
FsmRecvResetReq(struct fsm *fp, struct fsmheader *lhp, struct mbuf *bp)
{
  if ((*fp->fn->RecvResetReq)(fp)) {
    /*
     * All sendable compressed packets are queued in the first (lowest
     * priority) modem output queue.... dump 'em to the priority queue
     * so that they arrive at the peer before our ResetAck.
     */
    link_SequenceQueue(fp->link);
    fsm_Output(fp, CODE_RESETACK, lhp->id, NULL, 0, MB_CCPOUT);
  }
  m_freem(bp);
}