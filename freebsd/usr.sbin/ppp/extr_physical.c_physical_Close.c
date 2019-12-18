#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct utmpx {int /*<<< orphan*/  ut_id; int /*<<< orphan*/  ut_tv; int /*<<< orphan*/  ut_type; } ;
struct TYPE_9__ {char* full; char* base; } ;
struct TYPE_6__ {int /*<<< orphan*/  total; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; TYPE_1__ stats; } ;
struct physical {int fd; scalar_t__ session_owner; TYPE_4__ name; TYPE_3__* handler; TYPE_2__ link; TYPE_5__* dl; scalar_t__ Utmp; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_10__ {int /*<<< orphan*/  bundle; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* destroy ) (struct physical*) ;int /*<<< orphan*/  (* cooked ) (struct physical*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEAD_PROCESS ; 
 int /*<<< orphan*/  ID0kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID0logout (struct utmpx*) ; 
 int ID0unlink (char*) ; 
 int /*<<< orphan*/  LogALERT ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogPHASE ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SIGHUP ; 
 char* _PATH_VARRUN ; 
 int /*<<< orphan*/  bundle_setsid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getpgrp () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  log_SetTtyCommandMode (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (struct utmpx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  physical_StopDeviceTimer (struct physical*) ; 
 int /*<<< orphan*/  physical_Unlock (struct physical*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct physical*) ; 
 int /*<<< orphan*/  stub2 (struct physical*) ; 
 scalar_t__ tcgetpgrp (int) ; 
 int /*<<< orphan*/  throughput_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throughput_stop (int /*<<< orphan*/ *) ; 

void
physical_Close(struct physical *p)
{
  int newsid;
  char fn[PATH_MAX];
  struct utmpx ut;

  if (p->fd < 0)
    return;

  log_Printf(LogDEBUG, "%s: Close\n", p->link.name);

  if (p->handler && p->handler->cooked)
    (*p->handler->cooked)(p);

  physical_StopDeviceTimer(p);
  if (p->Utmp) {
    memset(&ut, 0, sizeof ut);
    ut.ut_type = DEAD_PROCESS;
    gettimeofday(&ut.ut_tv, NULL);
    snprintf(ut.ut_id, sizeof ut.ut_id, "%xppp", (int)getpid());
    ID0logout(&ut);
    p->Utmp = 0;
  }
  newsid = tcgetpgrp(p->fd) == getpgrp();
  close(p->fd);
  p->fd = -1;
  log_SetTtyCommandMode(p->dl);

  throughput_stop(&p->link.stats.total);
  throughput_log(&p->link.stats.total, LogPHASE, p->link.name);

  if (p->session_owner != (pid_t)-1) {
    log_Printf(LogPHASE, "%s: HUPing %ld\n", p->link.name,
               (long)p->session_owner);
    ID0kill(p->session_owner, SIGHUP);
    p->session_owner = (pid_t)-1;
  }

  if (newsid)
    bundle_setsid(p->dl->bundle, 0);

  if (*p->name.full == '/') {
    snprintf(fn, sizeof fn, "%s%s.if", _PATH_VARRUN, p->name.base);
    if (ID0unlink(fn) == -1)
      log_Printf(LogALERT, "%s: Can't remove %s: %s\n",
                 p->link.name, fn, strerror(errno));
  }
  physical_Unlock(p);
  if (p->handler && p->handler->destroy)
    (*p->handler->destroy)(p);
  p->handler = NULL;
  p->name.base = p->name.full;
  *p->name.full = '\0';
}