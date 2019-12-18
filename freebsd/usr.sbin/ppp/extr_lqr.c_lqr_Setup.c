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
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {char* name; int load; struct lcp* arg; int /*<<< orphan*/  func; } ;
struct TYPE_11__ {int peer_timeout; int /*<<< orphan*/  peer; scalar_t__ resent; } ;
struct TYPE_10__ {scalar_t__ seq_recv; scalar_t__ seq_sent; } ;
struct TYPE_13__ {int method; TYPE_8__ timer; TYPE_3__ lqr; TYPE_2__ echo; } ;
struct TYPE_14__ {TYPE_5__ lqm; } ;
struct physical {TYPE_7__ link; TYPE_6__ hdlc; } ;
struct TYPE_12__ {int lqrperiod; int /*<<< orphan*/  lqr; scalar_t__ echo; } ;
struct TYPE_9__ {int /*<<< orphan*/  link; } ;
struct lcp {int his_lqrperiod; int want_lqrperiod; TYPE_4__ cfg; TYPE_1__ fsm; } ;

/* Variables and functions */
 scalar_t__ IsEnabled (int /*<<< orphan*/ ) ; 
 int LQM_ECHO ; 
 int LQM_LQR ; 
 int /*<<< orphan*/  LogLQM ; 
 int /*<<< orphan*/  REJECTED (struct lcp*,int /*<<< orphan*/ ) ; 
 int SECTICKS ; 
 int /*<<< orphan*/  SendLqrReport ; 
 int /*<<< orphan*/  TY_QUALPROTO ; 
 struct physical* link2physical (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_8__*) ; 

__attribute__((used)) static void
lqr_Setup(struct lcp *lcp)
{
  struct physical *physical = link2physical(lcp->fsm.link);
  int period;

  physical->hdlc.lqm.lqr.resent = 0;
  physical->hdlc.lqm.echo.seq_sent = 0;
  physical->hdlc.lqm.echo.seq_recv = 0;
  memset(&physical->hdlc.lqm.lqr.peer, '\0',
         sizeof physical->hdlc.lqm.lqr.peer);

  physical->hdlc.lqm.method = lcp->cfg.echo ? LQM_ECHO : 0;
  if (IsEnabled(lcp->cfg.lqr) && !REJECTED(lcp, TY_QUALPROTO))
    physical->hdlc.lqm.method |= LQM_LQR;
  timer_Stop(&physical->hdlc.lqm.timer);

  physical->hdlc.lqm.lqr.peer_timeout = lcp->his_lqrperiod;
  if (lcp->his_lqrperiod)
    log_Printf(LogLQM, "%s: Expecting LQR every %d.%02d secs\n",
              physical->link.name, lcp->his_lqrperiod / 100,
              lcp->his_lqrperiod % 100);

  period = lcp->want_lqrperiod ?
    lcp->want_lqrperiod : lcp->cfg.lqrperiod * 100;
  physical->hdlc.lqm.timer.func = SendLqrReport;
  physical->hdlc.lqm.timer.name = "lqm";
  physical->hdlc.lqm.timer.arg = lcp;

  if (lcp->want_lqrperiod || physical->hdlc.lqm.method & LQM_ECHO) {
    log_Printf(LogLQM, "%s: Will send %s every %d.%02d secs\n",
              physical->link.name, lcp->want_lqrperiod ? "LQR" : "LCP ECHO",
              period / 100, period % 100);
    physical->hdlc.lqm.timer.load = period * SECTICKS / 100;
  } else {
    physical->hdlc.lqm.timer.load = 0;
    if (!lcp->his_lqrperiod)
      log_Printf(LogLQM, "%s: LQR/LCP ECHO not negotiated\n",
                 physical->link.name);
  }
}