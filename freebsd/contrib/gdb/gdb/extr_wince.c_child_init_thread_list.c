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
struct TYPE_4__ {int /*<<< orphan*/  h; struct TYPE_4__* next; } ;
typedef  TYPE_1__ thread_info ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENTS (char*) ; 
 int /*<<< orphan*/  close_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_thread_list () ; 
 TYPE_1__ thread_head ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

__attribute__((used)) static void
child_init_thread_list (void)
{
  thread_info *th = &thread_head;

  DEBUG_EVENTS (("gdb: child_init_thread_list\n"));
  init_thread_list ();
  while (th->next != NULL)
    {
      thread_info *here = th->next;
      th->next = here->next;
      (void) close_handle (here->h);
      xfree (here);
    }
}