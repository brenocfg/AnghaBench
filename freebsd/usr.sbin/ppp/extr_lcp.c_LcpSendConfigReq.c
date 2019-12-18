#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct physical {int dummy; } ;
struct TYPE_14__ {scalar_t__ class; size_t len; int /*<<< orphan*/  address; } ;
struct TYPE_15__ {TYPE_6__ enddisc; int /*<<< orphan*/  negenddisc; } ;
struct mp {TYPE_7__ cfg; } ;
struct TYPE_13__ {TYPE_4__* bundle; } ;
struct TYPE_10__ {int opmask; int /*<<< orphan*/  msg; } ;
struct TYPE_9__ {int max_mru; } ;
struct lcp {int want_mru; int want_auth; scalar_t__ want_authtype; int want_mrru; TYPE_5__ fsm; scalar_t__ want_shortseq; TYPE_2__ want_callback; scalar_t__ want_lqrperiod; scalar_t__ want_magic; TYPE_1__ cfg; scalar_t__ want_accmap; scalar_t__ want_protocomp; scalar_t__ want_acfcomp; } ;
struct fsm_opt {scalar_t__* data; } ;
struct fsm {int /*<<< orphan*/  reqid; TYPE_8__* link; } ;
struct TYPE_16__ {size_t name; } ;
struct TYPE_11__ {struct mp mp; } ;
struct TYPE_12__ {TYPE_3__ ncp; } ;

/* Variables and functions */
 void* CALLBACK_AUTH ; 
 int CALLBACK_BIT (void*) ; 
 void* CALLBACK_CBCP ; 
 void* CALLBACK_E164 ; 
 int /*<<< orphan*/  CODE_CONFIGREQ ; 
 int /*<<< orphan*/  INC_FSM_OPT (int /*<<< orphan*/ ,int,struct fsm_opt*) ; 
 scalar_t__ IsEnabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  MB_LCPOUT ; 
#define  PROTO_CHAP 129 
 int PROTO_LQR ; 
#define  PROTO_PAP 128 
 int /*<<< orphan*/  REJECTED (struct lcp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TY_ACCMAP ; 
 int /*<<< orphan*/  TY_ACFCOMP ; 
 int /*<<< orphan*/  TY_AUTHPROTO ; 
 int /*<<< orphan*/  TY_CALLBACK ; 
 int /*<<< orphan*/  TY_ENDDISC ; 
 int /*<<< orphan*/  TY_MAGICNUM ; 
 int /*<<< orphan*/  TY_MRRU ; 
 int /*<<< orphan*/  TY_MRU ; 
 int /*<<< orphan*/  TY_PROTOCOMP ; 
 int /*<<< orphan*/  TY_QUALPROTO ; 
 int /*<<< orphan*/  TY_SHORTSEQ ; 
 struct lcp* fsm2lcp (struct fsm*) ; 
 int /*<<< orphan*/  fsm_Output (struct fsm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct physical* link2physical (TYPE_8__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 
 int physical_DeviceMTU (struct physical*) ; 
 int /*<<< orphan*/  physical_IsSync (struct physical*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ua_htonl (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ua_htons (int*,scalar_t__*) ; 

__attribute__((used)) static void
LcpSendConfigReq(struct fsm *fp)
{
  /* Send config REQ please */
  struct physical *p = link2physical(fp->link);
  struct lcp *lcp = fsm2lcp(fp);
  u_char buff[200];
  struct fsm_opt *o;
  struct mp *mp;
  u_int16_t proto;
  u_short maxmru;

  if (!p) {
    log_Printf(LogERROR, "%s: LcpSendConfigReq: Not a physical link !\n",
              fp->link->name);
    return;
  }

  o = (struct fsm_opt *)buff;
  if (!physical_IsSync(p)) {
    if (lcp->want_acfcomp && !REJECTED(lcp, TY_ACFCOMP))
      INC_FSM_OPT(TY_ACFCOMP, 2, o);

    if (lcp->want_protocomp && !REJECTED(lcp, TY_PROTOCOMP))
      INC_FSM_OPT(TY_PROTOCOMP, 2, o);

    if (!REJECTED(lcp, TY_ACCMAP)) {
      ua_htonl(&lcp->want_accmap, o->data);
      INC_FSM_OPT(TY_ACCMAP, 6, o);
    }
  }

  maxmru = p ? physical_DeviceMTU(p) : 0;
  if (lcp->cfg.max_mru && (!maxmru || maxmru > lcp->cfg.max_mru))
    maxmru = lcp->cfg.max_mru;
  if (maxmru && lcp->want_mru > maxmru) {
    log_Printf(LogWARN, "%s: Reducing configured MRU from %u to %u\n",
               fp->link->name, lcp->want_mru, maxmru);
    lcp->want_mru = maxmru;
  }
  if (!REJECTED(lcp, TY_MRU)) {
    ua_htons(&lcp->want_mru, o->data);
    INC_FSM_OPT(TY_MRU, 4, o);
  }

  if (lcp->want_magic && !REJECTED(lcp, TY_MAGICNUM)) {
    ua_htonl(&lcp->want_magic, o->data);
    INC_FSM_OPT(TY_MAGICNUM, 6, o);
  }

  if (lcp->want_lqrperiod && !REJECTED(lcp, TY_QUALPROTO)) {
    proto = PROTO_LQR;
    ua_htons(&proto, o->data);
    ua_htonl(&lcp->want_lqrperiod, o->data + 2);
    INC_FSM_OPT(TY_QUALPROTO, 8, o);
  }

  switch (lcp->want_auth) {
  case PROTO_PAP:
    proto = PROTO_PAP;
    ua_htons(&proto, o->data);
    INC_FSM_OPT(TY_AUTHPROTO, 4, o);
    break;

  case PROTO_CHAP:
    proto = PROTO_CHAP;
    ua_htons(&proto, o->data);
    o->data[2] = lcp->want_authtype;
    INC_FSM_OPT(TY_AUTHPROTO, 5, o);
    break;
  }

  if (!REJECTED(lcp, TY_CALLBACK)) {
    if (lcp->want_callback.opmask & CALLBACK_BIT(CALLBACK_AUTH)) {
      *o->data = CALLBACK_AUTH;
      INC_FSM_OPT(TY_CALLBACK, 3, o);
    } else if (lcp->want_callback.opmask & CALLBACK_BIT(CALLBACK_CBCP)) {
      *o->data = CALLBACK_CBCP;
      INC_FSM_OPT(TY_CALLBACK, 3, o);
    } else if (lcp->want_callback.opmask & CALLBACK_BIT(CALLBACK_E164)) {
      size_t sz = strlen(lcp->want_callback.msg);

      if (sz > sizeof o->data - 1) {
        sz = sizeof o->data - 1;
        log_Printf(LogWARN, "Truncating E164 data to %zu octets (oops!)\n",
	    sz);
      }
      *o->data = CALLBACK_E164;
      memcpy(o->data + 1, lcp->want_callback.msg, sz);
      INC_FSM_OPT(TY_CALLBACK, sz + 3, o);
    }
  }

  if (lcp->want_mrru && !REJECTED(lcp, TY_MRRU)) {
    ua_htons(&lcp->want_mrru, o->data);
    INC_FSM_OPT(TY_MRRU, 4, o);

    if (lcp->want_shortseq && !REJECTED(lcp, TY_SHORTSEQ))
      INC_FSM_OPT(TY_SHORTSEQ, 2, o);
  }

  mp = &lcp->fsm.bundle->ncp.mp;
  if (mp->cfg.enddisc.class != 0 && IsEnabled(mp->cfg.negenddisc) &&
      !REJECTED(lcp, TY_ENDDISC)) {
    *o->data = mp->cfg.enddisc.class;
    memcpy(o->data+1, mp->cfg.enddisc.address, mp->cfg.enddisc.len);
    INC_FSM_OPT(TY_ENDDISC, mp->cfg.enddisc.len + 3, o);
  }

  fsm_Output(fp, CODE_CONFIGREQ, fp->reqid, buff, (u_char *)o - buff,
             MB_LCPOUT);
}