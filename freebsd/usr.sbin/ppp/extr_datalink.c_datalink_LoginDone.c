#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int tries; scalar_t__ incs; } ;
struct TYPE_14__ {int /*<<< orphan*/  logout; } ;
struct TYPE_15__ {TYPE_2__ script; } ;
struct TYPE_13__ {scalar_t__ run; int /*<<< orphan*/  packetmode; } ;
struct datalink {scalar_t__ state; TYPE_7__* physical; TYPE_4__ dial; TYPE_3__ cfg; int /*<<< orphan*/  chat; TYPE_1__ script; } ;
struct TYPE_17__ {int /*<<< orphan*/  openmode; } ;
struct TYPE_12__ {int /*<<< orphan*/  fsm; TYPE_5__ cfg; } ;
struct TYPE_18__ {TYPE_10__ lcp; int /*<<< orphan*/  ccp; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_6__ link; int /*<<< orphan*/  async; int /*<<< orphan*/  hdlc; } ;

/* Variables and functions */
 scalar_t__ DATALINK_LCP ; 
 scalar_t__ DATALINK_LOGOUT ; 
 scalar_t__ DATALINK_READY ; 
 int /*<<< orphan*/  LogWARN ; 
 scalar_t__ PHYS_DEDICATED ; 
 int /*<<< orphan*/  async_Setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccp_Setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chat_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chat_Setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  datalink_HangupDone (struct datalink*) ; 
 int /*<<< orphan*/  datalink_NewState (struct datalink*,scalar_t__) ; 
 int /*<<< orphan*/  fsm_Open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_Up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdlc_Init (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  lcp_Setup (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  physical_Close (TYPE_7__*) ; 
 int /*<<< orphan*/  physical_Raw (TYPE_7__*) ; 
 int /*<<< orphan*/  physical_StopDeviceTimer (TYPE_7__*) ; 

__attribute__((used)) static void
datalink_LoginDone(struct datalink *dl)
{
  chat_Finish(&dl->chat);

  if (!dl->script.packetmode) {
    dl->dial.tries = -1;
    dl->dial.incs = 0;
    datalink_NewState(dl, DATALINK_READY);
  } else if (!physical_Raw(dl->physical)) {
    dl->dial.tries = 0;
    log_Printf(LogWARN, "datalink_LoginDone: Not connected.\n");
    if (dl->script.run) {
      datalink_NewState(dl, DATALINK_LOGOUT);
      if (!chat_Setup(&dl->chat, dl->cfg.script.logout, NULL))
        log_Printf(LogWARN, "Invalid logout script\n");
    } else {
      physical_StopDeviceTimer(dl->physical);
      if (dl->physical->type == PHYS_DEDICATED)
        /* force a redial timeout */
        physical_Close(dl->physical);
      datalink_HangupDone(dl);
    }
  } else {
    dl->dial.tries = -1;
    dl->dial.incs = 0;

    hdlc_Init(&dl->physical->hdlc, &dl->physical->link.lcp);
    async_Setup(&dl->physical->async);

    lcp_Setup(&dl->physical->link.lcp, dl->state == DATALINK_READY ?
              0 : dl->physical->link.lcp.cfg.openmode);
    ccp_Setup(&dl->physical->link.ccp);

    datalink_NewState(dl, DATALINK_LCP);
    fsm_Up(&dl->physical->link.lcp.fsm);
    fsm_Open(&dl->physical->link.lcp.fsm);
  }
}