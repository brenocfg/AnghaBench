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
struct TYPE_5__ {int /*<<< orphan*/  logout; int /*<<< orphan*/  hangup; } ;
struct TYPE_6__ {TYPE_2__ script; } ;
struct TYPE_4__ {scalar_t__ run; } ;
struct datalink {int stayonline; scalar_t__ state; TYPE_3__ cfg; int /*<<< orphan*/  chat; TYPE_1__ script; int /*<<< orphan*/  physical; } ;

/* Variables and functions */
 int CLOSE_LCP ; 
 int CLOSE_STAYDOWN ; 
 scalar_t__ DATALINK_CLOSED ; 
 scalar_t__ DATALINK_HANGUP ; 
 scalar_t__ DATALINK_LOGOUT ; 
 scalar_t__ DATALINK_OPENING ; 
 scalar_t__ DATALINK_READY ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  chat_Setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  datalink_DontHangup (struct datalink*) ; 
 int /*<<< orphan*/  datalink_HangupDone (struct datalink*) ; 
 int /*<<< orphan*/  datalink_NewState (struct datalink*,scalar_t__) ; 
 int /*<<< orphan*/  datalink_StayDown (struct datalink*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  physical_Offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physical_StopDeviceTimer (int /*<<< orphan*/ ) ; 

void
datalink_ComeDown(struct datalink *dl, int how)
{
  int stayonline;

  if (how == CLOSE_LCP)
    datalink_DontHangup(dl);
  else if (how == CLOSE_STAYDOWN)
    datalink_StayDown(dl);

  stayonline = dl->stayonline;
  dl->stayonline = 0;

  if (dl->state >= DATALINK_READY && stayonline) {
    physical_StopDeviceTimer(dl->physical);
    datalink_NewState(dl, DATALINK_READY);
  } else if (dl->state != DATALINK_CLOSED && dl->state != DATALINK_HANGUP) {
    physical_Offline(dl->physical);
    if (dl->script.run && dl->state != DATALINK_OPENING) {
      if (dl->state == DATALINK_LOGOUT) {
        datalink_NewState(dl, DATALINK_HANGUP);
        if (!chat_Setup(&dl->chat, dl->cfg.script.hangup, NULL))
          log_Printf(LogWARN, "Invalid hangup script\n");
      } else {
        datalink_NewState(dl, DATALINK_LOGOUT);
        if (!chat_Setup(&dl->chat, dl->cfg.script.logout, NULL))
          log_Printf(LogWARN, "Invalid logout script\n");
      }
    } else
      datalink_HangupDone(dl);
  }
}