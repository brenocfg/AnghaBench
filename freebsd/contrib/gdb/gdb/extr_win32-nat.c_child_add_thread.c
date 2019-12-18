#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ ContextFlags; void* Dr7; void* Dr3; void* Dr2; void* Dr1; void* Dr0; } ;
struct TYPE_8__ {TYPE_6__ context; int /*<<< orphan*/  h; struct TYPE_8__* next; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ thread_info ;
struct TYPE_9__ {TYPE_1__* next; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 scalar_t__ CONTEXT_DEBUG_REGISTERS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetThreadContext (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  SetThreadContext (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_registers_used ; 
 void** dr ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pid_to_ptid (int /*<<< orphan*/ ) ; 
 TYPE_3__ thread_head ; 
 TYPE_1__* thread_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static thread_info *
child_add_thread (DWORD id, HANDLE h)
{
  thread_info *th;

  if ((th = thread_rec (id, FALSE)))
    return th;

  th = (thread_info *) xmalloc (sizeof (*th));
  memset (th, 0, sizeof (*th));
  th->id = id;
  th->h = h;
  th->next = thread_head.next;
  thread_head.next = th;
  add_thread (pid_to_ptid (id));
  /* Set the debug registers for the new thread in they are used.  */
  if (debug_registers_used)
    {
      /* Only change the value of the debug registers.  */
      th->context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
      CHECK (GetThreadContext (th->h, &th->context));
      th->context.Dr0 = dr[0];
      th->context.Dr1 = dr[1];
      th->context.Dr2 = dr[2];
      th->context.Dr3 = dr[3];
      /* th->context.Dr6 = dr[6];
      FIXME: should we set dr6 also ?? */
      th->context.Dr7 = dr[7];
      CHECK (SetThreadContext (th->h, &th->context));
      th->context.ContextFlags = 0;
    }
  return th;
}