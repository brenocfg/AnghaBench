#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_18__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_36__ {unsigned int* neg; } ;
struct TYPE_37__ {TYPE_6__ cfg; } ;
struct link {TYPE_7__ ccp; } ;
struct datalink {TYPE_18__* physical; int /*<<< orphan*/  name; } ;
struct cmdargs {int argn; TYPE_19__* bundle; TYPE_14__* cmd; int /*<<< orphan*/ * argv; struct datalink* cx; } ;
struct TYPE_38__ {unsigned int negenddisc; unsigned int shortseq; } ;
struct TYPE_39__ {TYPE_8__ cfg; } ;
struct TYPE_33__ {int load; int /*<<< orphan*/  (* func ) (TYPE_17__*) ;} ;
struct TYPE_34__ {int method; TYPE_3__ timer; } ;
struct TYPE_35__ {TYPE_4__ lqm; } ;
struct TYPE_32__ {int /*<<< orphan*/  state; } ;
struct TYPE_31__ {unsigned int dns_neg; } ;
struct TYPE_21__ {unsigned int neg; } ;
struct TYPE_22__ {TYPE_10__ vj; TYPE_1__ ns; } ;
struct TYPE_23__ {TYPE_11__ cfg; } ;
struct TYPE_24__ {TYPE_12__ ipcp; TYPE_9__ mp; } ;
struct TYPE_30__ {TYPE_13__ ncp; } ;
struct TYPE_26__ {unsigned int acfcomp; unsigned int chap05; unsigned int chap80nt; unsigned int chap80lm; unsigned int chap81; int echo; int lqrperiod; unsigned int lqr; unsigned int pap; unsigned int protocomp; } ;
struct TYPE_28__ {TYPE_15__ cfg; TYPE_2__ fsm; int /*<<< orphan*/  want_lqrperiod; } ;
struct TYPE_27__ {TYPE_17__ lcp; } ;
struct TYPE_29__ {TYPE_16__ link; TYPE_5__ hdlc; } ;
struct TYPE_25__ {int lauth; int /*<<< orphan*/  name; scalar_t__ args; } ;

/* Variables and functions */
 size_t CCP_NEG_DEFLATE ; 
 size_t CCP_NEG_DEFLATE24 ; 
 size_t CCP_NEG_MPPE ; 
 size_t CCP_NEG_PRED1 ; 
 int /*<<< orphan*/  DATALINK_LCP ; 
 int LOCAL_CX ; 
 int LOCAL_CX_OPT ; 
 int LQM_ECHO ; 
 int /*<<< orphan*/  LogWARN ; 
#define  NEG_ACFCOMP 146 
#define  NEG_CHAP05 145 
#define  NEG_CHAP80 144 
#define  NEG_CHAP80LM 143 
#define  NEG_CHAP81 142 
#define  NEG_DEFLATE 141 
#define  NEG_DNS 140 
#define  NEG_ECHO 139 
#define  NEG_ENDDISC 138 
#define  NEG_LQR 137 
#define  NEG_MPPE 136 
#define  NEG_PAP 135 
#define  NEG_PPPDDEFLATE 134 
#define  NEG_PRED1 133 
#define  NEG_PROTOCOMP 132 
#define  NEG_SHORTSEQ 131 
#define  NEG_VJCOMP 130 
#define  PHASE_DEAD 129 
#define  PHASE_ESTABLISH 128 
 int SECTICKS ; 
 int /*<<< orphan*/  ST_OPENED ; 
 int /*<<< orphan*/  bundle_HighestState (TYPE_19__*) ; 
 int /*<<< orphan*/  bundle_Phase (TYPE_19__*) ; 
 struct link* command_ChooseLink (struct cmdargs const*) ; 
 char* ident_cmd (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lqr_StopTimer (TYPE_18__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_17__*) ; 

__attribute__((used)) static int
NegotiateSet(struct cmdargs const *arg)
{
  long param = (long)arg->cmd->args;
  struct link *l = command_ChooseLink(arg);	/* LOCAL_CX_OPT uses this */
  struct datalink *cx = arg->cx;	/* LOCAL_CX uses this */
  const char *cmd;
  unsigned keep;			/* Keep these bits */
  unsigned add;				/* Add these bits */

  if ((cmd = ident_cmd(arg->argv[arg->argn-2], &keep, &add)) == NULL)
    return 1;

  if ((arg->cmd->lauth & LOCAL_CX) && !cx) {
    log_Printf(LogWARN, "%s %s: No context (use the `link' command)\n",
              cmd, arg->cmd->name);
    return 2;
  } else if (cx && !(arg->cmd->lauth & (LOCAL_CX|LOCAL_CX_OPT))) {
    log_Printf(LogWARN, "%s %s: Redundant context (%s) ignored\n",
              cmd, arg->cmd->name, cx->name);
    cx = NULL;
  }

  switch (param) {
    case NEG_ACFCOMP:
      cx->physical->link.lcp.cfg.acfcomp &= keep;
      cx->physical->link.lcp.cfg.acfcomp |= add;
      break;
    case NEG_CHAP05:
      cx->physical->link.lcp.cfg.chap05 &= keep;
      cx->physical->link.lcp.cfg.chap05 |= add;
      break;
#ifndef NODES
    case NEG_CHAP80:
      cx->physical->link.lcp.cfg.chap80nt &= keep;
      cx->physical->link.lcp.cfg.chap80nt |= add;
      break;
    case NEG_CHAP80LM:
      cx->physical->link.lcp.cfg.chap80lm &= keep;
      cx->physical->link.lcp.cfg.chap80lm |= add;
      break;
    case NEG_CHAP81:
      cx->physical->link.lcp.cfg.chap81 &= keep;
      cx->physical->link.lcp.cfg.chap81 |= add;
      break;
    case NEG_MPPE:
      l->ccp.cfg.neg[CCP_NEG_MPPE] &= keep;
      l->ccp.cfg.neg[CCP_NEG_MPPE] |= add;
      break;
#endif
    case NEG_DEFLATE:
      l->ccp.cfg.neg[CCP_NEG_DEFLATE] &= keep;
      l->ccp.cfg.neg[CCP_NEG_DEFLATE] |= add;
      break;
    case NEG_DNS:
      arg->bundle->ncp.ipcp.cfg.ns.dns_neg &= keep;
      arg->bundle->ncp.ipcp.cfg.ns.dns_neg |= add;
      break;
    case NEG_ECHO:	/* probably misplaced in this function ! */
      if (cx->physical->link.lcp.cfg.echo && !add) {
        cx->physical->link.lcp.cfg.echo = 0;
        cx->physical->hdlc.lqm.method &= ~LQM_ECHO;
        if (cx->physical->hdlc.lqm.method & LQM_ECHO &&
            !cx->physical->link.lcp.want_lqrperiod && 
            cx->physical->hdlc.lqm.timer.load) {
          cx->physical->hdlc.lqm.timer.load = 0;
          lqr_StopTimer(cx->physical);
        }
      } else if (!cx->physical->link.lcp.cfg.echo && add) {
        cx->physical->link.lcp.cfg.echo = 1;
        cx->physical->hdlc.lqm.method |= LQM_ECHO;
        cx->physical->hdlc.lqm.timer.load =
	    cx->physical->link.lcp.cfg.lqrperiod * SECTICKS;
        if (cx->physical->link.lcp.fsm.state == ST_OPENED)
          (*cx->physical->hdlc.lqm.timer.func)(&cx->physical->link.lcp);
      }
      break;
    case NEG_ENDDISC:
      arg->bundle->ncp.mp.cfg.negenddisc &= keep;
      arg->bundle->ncp.mp.cfg.negenddisc |= add;
      break;
    case NEG_LQR:
      cx->physical->link.lcp.cfg.lqr &= keep;
      cx->physical->link.lcp.cfg.lqr |= add;
      break;
    case NEG_PAP:
      cx->physical->link.lcp.cfg.pap &= keep;
      cx->physical->link.lcp.cfg.pap |= add;
      break;
    case NEG_PPPDDEFLATE:
      l->ccp.cfg.neg[CCP_NEG_DEFLATE24] &= keep;
      l->ccp.cfg.neg[CCP_NEG_DEFLATE24] |= add;
      break;
    case NEG_PRED1:
      l->ccp.cfg.neg[CCP_NEG_PRED1] &= keep;
      l->ccp.cfg.neg[CCP_NEG_PRED1] |= add;
      break;
    case NEG_PROTOCOMP:
      cx->physical->link.lcp.cfg.protocomp &= keep;
      cx->physical->link.lcp.cfg.protocomp |= add;
      break;
    case NEG_SHORTSEQ:
      switch (bundle_Phase(arg->bundle)) {
        case PHASE_DEAD:
          break;
        case PHASE_ESTABLISH:
          /* Make sure none of our links are DATALINK_LCP or greater */
          if (bundle_HighestState(arg->bundle) >= DATALINK_LCP) {
            log_Printf(LogWARN, "shortseq: Only changeable before"
                       " LCP negotiations\n");
            return 1;
          }
          break;
        default:
          log_Printf(LogWARN, "shortseq: Only changeable at phase"
                     " DEAD/ESTABLISH\n");
          return 1;
      }
      arg->bundle->ncp.mp.cfg.shortseq &= keep;
      arg->bundle->ncp.mp.cfg.shortseq |= add;
      break;
    case NEG_VJCOMP:
      arg->bundle->ncp.ipcp.cfg.vj.neg &= keep;
      arg->bundle->ncp.ipcp.cfg.vj.neg |= add;
      break;
  }

  return 0;
}