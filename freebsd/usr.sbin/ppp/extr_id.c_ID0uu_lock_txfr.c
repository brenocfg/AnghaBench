#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ID0set0 () ; 
 int /*<<< orphan*/  ID0setuser () ; 
 int /*<<< orphan*/  LogID0 ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,char const*,long) ; 
 int uu_lock_txfr (char const*,scalar_t__) ; 

int
ID0uu_lock_txfr(const char *basettyname, pid_t newpid)
{
  int ret;

  ID0set0();
  ret = uu_lock_txfr(basettyname, newpid);
  log_Printf(LogID0, "%d = uu_lock_txfr(\"%s\", %ld)\n", ret, basettyname,
             (long)newpid);
  ID0setuser();
  return ret;
}