#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ id; int suspend_count; int reload_context; int /*<<< orphan*/  h; struct TYPE_5__* next; } ;
typedef  TYPE_1__ thread_info ;
struct TYPE_6__ {scalar_t__ dwThreadId; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int SuspendThread (int /*<<< orphan*/ ) ; 
 TYPE_4__ current_event ; 
 TYPE_1__ thread_head ; 

__attribute__((used)) static thread_info *
thread_rec (DWORD id, int get_context)
{
  thread_info *th;

  for (th = &thread_head; (th = th->next) != NULL;)
    if (th->id == id)
      {
	if (!th->suspend_count && get_context)
	  {
	    if (get_context > 0 && id != current_event.dwThreadId)
	      th->suspend_count = SuspendThread (th->h) + 1;
	    else if (get_context < 0)
	      th->suspend_count = -1;
	    th->reload_context = 1;
	  }
	return th;
      }

  return NULL;
}