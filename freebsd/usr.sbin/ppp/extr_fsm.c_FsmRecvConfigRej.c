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
struct fsm {int state; TYPE_3__* parent; TYPE_2__* fn; int /*<<< orphan*/  LogLevel; TYPE_1__* link; } ;
struct TYPE_6__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* LayerDown ) (int /*<<< orphan*/ ,struct fsm*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* LayerDown ) (struct fsm*) ;int /*<<< orphan*/  (* DecodeConfig ) (struct fsm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fsm_decode*) ;int /*<<< orphan*/  (* SendTerminateAck ) (struct fsm*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  lcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSM_REQ_TIMER ; 
 int /*<<< orphan*/  FsmInitRestartCounter (struct fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmSendConfigReq (struct fsm*) ; 
 int /*<<< orphan*/ * MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MODE_REJ ; 
 int /*<<< orphan*/  NewState (struct fsm*,int const) ; 
#define  ST_ACKRCVD 137 
#define  ST_ACKSENT 136 
#define  ST_CLOSED 135 
#define  ST_CLOSING 134 
#define  ST_INITIAL 133 
#define  ST_OPENED 132 
#define  ST_REQSENT 131 
#define  ST_STARTING 130 
#define  ST_STOPPED 129 
#define  ST_STOPPING 128 
 int /*<<< orphan*/  State2Nam (int) ; 
 int /*<<< orphan*/  lcp_SendIdentification (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 size_t m_length (struct mbuf*) ; 
 struct mbuf* m_pullup (struct mbuf*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct fsm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fsm_decode*) ; 
 int /*<<< orphan*/  stub3 (struct fsm*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,struct fsm*) ; 

__attribute__((used)) static void
FsmRecvConfigRej(struct fsm *fp, struct fsmheader *lhp, struct mbuf *bp)
/* RCJ */
{
  struct fsm_decode dec;
  size_t plen;
  int flen;
  u_char *cp;

  plen = m_length(bp);
  flen = ntohs(lhp->length) - sizeof *lhp;
  if ((int)plen < flen) {
    m_freem(bp);
    return;
  }

  lcp_SendIdentification(&fp->link->lcp);

  /*
   * Check and process easy case
   */
  switch (fp->state) {
  case ST_INITIAL:
  case ST_STARTING:
    log_Printf(fp->LogLevel, "%s: Oops, RCJ in %s.\n",
              fp->link->name, State2Nam(fp->state));
    m_freem(bp);
    return;
  case ST_CLOSED:
  case ST_STOPPED:
    (*fp->fn->SendTerminateAck)(fp, lhp->id);
    m_freem(bp);
    return;
  case ST_CLOSING:
  case ST_STOPPING:
    m_freem(bp);
    return;
  }

  bp = m_pullup(bp);
  dec.ackend = dec.ack;
  dec.nakend = dec.nak;
  dec.rejend = dec.rej;
  cp = MBUF_CTOP(bp);
  (*fp->fn->DecodeConfig)(fp, cp, cp + flen, MODE_REJ, &dec);
  if (flen < (int)sizeof(struct fsm_opt_hdr))
    log_Printf(fp->LogLevel, "  [EMPTY]\n");

  switch (fp->state) {
  case ST_REQSENT:
  case ST_ACKSENT:
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    FsmSendConfigReq(fp);
    break;
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
    break;
  case ST_ACKRCVD:
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    break;
  }
  m_freem(bp);
}