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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct physical {TYPE_1__ name; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int ID0uu_lock_txfr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogPHASE ; 
 int UU_LOCK_OK ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ physical_LockedDevice (struct physical*) ; 
 int /*<<< orphan*/  uu_lockerr (int) ; 

void
physical_ChangedPid(struct physical *p, pid_t newpid)
{
  if (physical_LockedDevice(p)) {
    int res;

    if ((res = ID0uu_lock_txfr(p->name.base, newpid)) != UU_LOCK_OK)
      log_Printf(LogPHASE, "uu_lock_txfr: %s\n", uu_lockerr(res));
  }
}