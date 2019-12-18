#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Dr7; int /*<<< orphan*/  Dr6; int /*<<< orphan*/  Dr3; int /*<<< orphan*/  Dr2; int /*<<< orphan*/  Dr1; int /*<<< orphan*/  Dr0; int /*<<< orphan*/  ContextFlags; } ;
struct TYPE_4__ {scalar_t__ reload_context; TYPE_3__ context; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ thread_info ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_DEBUGGER_DR ; 
 int /*<<< orphan*/  GetThreadContext (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int I387_FISEG_REGNUM ; 
 int I387_FOP_REGNUM ; 
 int NUM_REGS ; 
 TYPE_1__* current_thread ; 
 int /*<<< orphan*/ * dr ; 
 int* mappings ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

__attribute__((used)) static void
do_child_fetch_inferior_registers (int r)
{
  char *context_offset = ((char *) &current_thread->context) + mappings[r];
  long l;

  if (!current_thread)
    return;	/* Windows sometimes uses a non-existent thread id in its
		   events */

  if (current_thread->reload_context)
    {
      thread_info *th = current_thread;
      th->context.ContextFlags = CONTEXT_DEBUGGER_DR;
      GetThreadContext (th->h, &th->context);
      /* Copy dr values from that thread.  */
      dr[0] = th->context.Dr0;
      dr[1] = th->context.Dr1;
      dr[2] = th->context.Dr2;
      dr[3] = th->context.Dr3;
      dr[6] = th->context.Dr6;
      dr[7] = th->context.Dr7;
      current_thread->reload_context = 0;
    }

#define I387_ST0_REGNUM I386_ST0_REGNUM

  if (r == I387_FISEG_REGNUM)
    {
      l = *((long *) context_offset) & 0xffff;
      supply_register (r, (char *) &l);
    }
  else if (r == I387_FOP_REGNUM)
    {
      l = (*((long *) context_offset) >> 16) & ((1 << 11) - 1);
      supply_register (r, (char *) &l);
    }
  else if (r >= 0)
    supply_register (r, context_offset);
  else
    {
      for (r = 0; r < NUM_REGS; r++)
	do_child_fetch_inferior_registers (r);
    }

#undef I387_ST0_REGNUM
}