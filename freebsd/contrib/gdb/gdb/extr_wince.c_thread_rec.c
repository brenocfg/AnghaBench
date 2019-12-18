#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ContextFlags; } ;
struct TYPE_6__ {scalar_t__ id; int suspend_count; TYPE_5__ context; int /*<<< orphan*/  h; struct TYPE_6__* next; } ;
typedef  TYPE_1__ thread_info ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_DEBUGGER ; 
 int /*<<< orphan*/  get_thread_context (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int suspend_thread (int /*<<< orphan*/ ) ; 
 TYPE_1__* this_thread ; 
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
	    if (get_context > 0 && th != this_thread)
	      th->suspend_count = suspend_thread (th->h) + 1;
	    else if (get_context < 0)
	      th->suspend_count = -1;

	    th->context.ContextFlags = CONTEXT_DEBUGGER;
	    get_thread_context (th->h, &th->context);
	  }
	return th;
      }

  return NULL;
}