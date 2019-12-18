#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ id; int /*<<< orphan*/  h; struct TYPE_4__* next; } ;
typedef  TYPE_1__ thread_info ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  pid_to_ptid (scalar_t__) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 TYPE_1__ thread_head ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

__attribute__((used)) static void
child_delete_thread (DWORD id)
{
  thread_info *th;

  if (info_verbose)
    printf_unfiltered ("[Deleting %s]\n", target_pid_to_str (pid_to_ptid (id)));
  delete_thread (pid_to_ptid (id));

  for (th = &thread_head;
       th->next != NULL && th->next->id != id;
       th = th->next)
    continue;

  if (th->next != NULL)
    {
      thread_info *here = th->next;
      th->next = here->next;
      CloseHandle (here->h);
      xfree (here);
    }
}