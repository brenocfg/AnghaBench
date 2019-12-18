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
struct TYPE_2__ {int dwProcessId; } ;

/* Variables and functions */
 TYPE_1__ current_event ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,...) ; 

char *
cygwin_pid_to_str (int pid)
{
  static char buf[80];
  if (pid == current_event.dwProcessId)
    sprintf (buf, "process %d", pid);
  else
    sprintf (buf, "thread %d.0x%x", (unsigned) current_event.dwProcessId, pid);
  return buf;
}