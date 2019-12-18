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
 int kill (scalar_t__,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,long,int) ; 

int
ID0kill(pid_t pid, int sig)
{
  int result;

  ID0set0();
  result = kill(pid, sig);
  log_Printf(LogID0, "%d = kill(%ld, %d)\n", result, (long)pid, sig);
  ID0setuser();
  return result;
}