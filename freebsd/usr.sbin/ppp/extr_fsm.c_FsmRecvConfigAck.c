#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct mbuf {int dummy; } ;
struct fsmheader {int /*<<< orphan*/  id; int /*<<< orphan*/  length; } ;
struct fsm_opt_hdr {int dummy; } ;
struct fsm_decode {int /*<<< orphan*/  rej; int /*<<< orphan*/  rejend; int /*<<< orphan*/  nak; int /*<<< orphan*/  nakend; int /*<<< orphan*/  ack; int /*<<< orphan*/  ackend; } ;
struct fsm {int state; TYPE_3__* parent; TYPE_2__* fn; TYPE_1__* link; int /*<<< orphan*/  LogLevel; } ;
struct TYPE_6__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* LayerDown ) (int /*<<< orphan*/ ,struct fsm*) ;int /*<<< orphan*/  (* LayerUp ) (int /*<<< orphan*/ ,struct fsm*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* LayerDown ) (struct fsm*) ;int /*<<< orphan*/  (* LayerUp ) (struct fsm*) ;int /*<<< orphan*/  (* SendTerminateAck ) (struct fsm*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DecodeConfig ) (struct fsm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fsm_decode*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  lcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSM_REQ_TIMER ; 
 int /*<<< orphan*/  FSM_TRM_TIMER ; 
 int /*<<< orphan*/  FsmInitRestartCounter (struct fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmSendConfigReq (struct fsm*) ; 
 int /*<<< orphan*/  FsmSendTerminateReq (struct fsm*) ; 
 int /*<<< orphan*/ * MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MODE_ACK ; 
 int /*<<< orphan*/  NewState (struct fsm*,int const) ; 
#define  ST_ACKRCVD 135 
#define  ST_ACKSENT 134 
#define  ST_CLOSED 133 
#define  ST_CLOSING 132 
#define  ST_OPENED 131 
#define  ST_REQSENT 130 
#define  ST_STOPPED 129 
#define  ST_STOPPING 128 
 int /*<<< orphan*/  lcp_SendIdentification (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int m_length (struct mbuf*) ; 
 struct mbuf* m_pullup (struct mbuf*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fsm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fsm_decode*) ; 
 int /*<<< orphan*/  stub2 (struct fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct fsm*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,struct fsm*) ; 
 int /*<<< orphan*/  stub5 (struct fsm*) ; 
 int /*<<< orphan*/  stub6 (struct fsm*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,struct fsm*) ; 

__attribute__((used)) static void
FsmRecvConfigAck(struct fsm *fp, struct fsmheader *lhp, struct mbuf *bp)
/* RCA */
{
  struct fsm_decode dec;
  int plen, flen;
  u_char *cp;

  plen = m_length(bp);
  flen = ntohs(lhp->length) - sizeof *lhp;
  if (plen < flen) {
    m_freem(bp);
    return;
  }

  bp = m_pullup(bp);
  dec.ackend = dec.ack;
  dec.nakend = dec.nak;
  dec.rejend = dec.rej;
  cp = MBUF_CTOP(bp);
  (*fp->fn->DecodeConfig)(fp, cp, cp + flen, MODE_ACK, &dec);
  if (flen < (int)sizeof(struct fsm_opt_hdr))
    log_Printf(fp->LogLevel, "  [EMPTY]\n");

  switch (fp->state) {
    case ST_CLOSED:
    case ST_STOPPED:
    (*fp->fn->SendTerminateAck)(fp, lhp->id);
    break;
  case ST_CLOSING:
  case ST_STOPPING:
    break;
  case ST_REQSENT:
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    NewState(fp, ST_ACKRCVD);
    break;
  case ST_ACKRCVD:
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    break;
  case ST_ACKSENT:
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    NewState(fp, ST_OPENED);
    if ((*fp->fn->LayerUp)(fp))
      (*fp->parent->LayerUp)(fp->parent->object, fp);
    else {
      (*fp->fn->LayerDown)(fp);
      FsmInitRestartCounter(fp, FSM_TRM_TIMER);
      FsmSendTerminateReq(fp);
      NewState(fp, ST_CLOSING);
      lcp_SendIdentification(&fp->link->lcp);
    }
    break;
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
    break;
  }
  m_freem(bp);
}