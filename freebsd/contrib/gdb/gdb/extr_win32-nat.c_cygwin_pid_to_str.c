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
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_2__ {int /*<<< orphan*/  dwProcessId; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 TYPE_1__ current_event ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

char *
cygwin_pid_to_str (ptid_t ptid)
{
  static char buf[80];
  int pid = PIDGET (ptid);

  if ((DWORD) pid == current_event.dwProcessId)
    sprintf (buf, "process %d", pid);
  else
    sprintf (buf, "thread %ld.0x%x", current_event.dwProcessId, pid);
  return buf;
}