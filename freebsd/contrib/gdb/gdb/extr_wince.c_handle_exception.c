#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* sig; } ;
struct target_waitstatus {TYPE_4__ value; int /*<<< orphan*/  kind; } ;
struct TYPE_7__ {int ExceptionCode; int /*<<< orphan*/  ExceptionAddress; } ;
struct TYPE_8__ {TYPE_1__ ExceptionRecord; scalar_t__ dwFirstChance; } ;
struct TYPE_9__ {TYPE_2__ Exception; } ;
struct TYPE_11__ {TYPE_3__ u; } ;

/* Variables and functions */
#define  DBG_CONTROL_C 133 
 int /*<<< orphan*/  DEBUG_EXCEPT (char*) ; 
#define  EXCEPTION_ACCESS_VIOLATION 132 
#define  EXCEPTION_BREAKPOINT 131 
#define  EXCEPTION_ILLEGAL_INSTRUCTION 130 
#define  EXCEPTION_SINGLE_STEP 129 
 int /*<<< orphan*/  SIGINT ; 
#define  STATUS_STACK_OVERFLOW 128 
 int /*<<< orphan*/  TARGET_SIGNAL_ILL ; 
 void* TARGET_SIGNAL_INT ; 
 void* TARGET_SIGNAL_SEGV ; 
 void* TARGET_SIGNAL_TRAP ; 
 void* TARGET_SIGNAL_UNKNOWN ; 
 int /*<<< orphan*/  TARGET_WAITKIND_STOPPED ; 
 void* check_for_step (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__ current_event ; 
 int /*<<< orphan*/  exception_count ; 
 int /*<<< orphan*/  last_sig ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
handle_exception (struct target_waitstatus *ourstatus)
{
#if 0
  if (current_event.u.Exception.dwFirstChance)
    return 0;
#endif

  ourstatus->kind = TARGET_WAITKIND_STOPPED;

  switch (current_event.u.Exception.ExceptionRecord.ExceptionCode)
    {
    case EXCEPTION_ACCESS_VIOLATION:
      DEBUG_EXCEPT (("gdb: Target exception ACCESS_VIOLATION at 0x%08x\n",
		     (unsigned) current_event.u.Exception.ExceptionRecord.ExceptionAddress));
      ourstatus->value.sig = TARGET_SIGNAL_SEGV;
      break;
    case STATUS_STACK_OVERFLOW:
      DEBUG_EXCEPT (("gdb: Target exception STACK_OVERFLOW at 0x%08x\n",
		     (unsigned) current_event.u.Exception.ExceptionRecord.ExceptionAddress));
      ourstatus->value.sig = TARGET_SIGNAL_SEGV;
      break;
    case EXCEPTION_BREAKPOINT:
      DEBUG_EXCEPT (("gdb: Target exception BREAKPOINT at 0x%08x\n",
		     (unsigned) current_event.u.Exception.ExceptionRecord.ExceptionAddress));
      ourstatus->value.sig = TARGET_SIGNAL_TRAP;
      break;
    case DBG_CONTROL_C:
      DEBUG_EXCEPT (("gdb: Target exception CONTROL_C at 0x%08x\n",
		     (unsigned) current_event.u.Exception.ExceptionRecord.ExceptionAddress));
      ourstatus->value.sig = TARGET_SIGNAL_INT;
      /* User typed CTRL-C.  Continue with this status */
      last_sig = SIGINT;	/* FIXME - should check pass state */
      break;
    case EXCEPTION_SINGLE_STEP:
      DEBUG_EXCEPT (("gdb: Target exception SINGLE_STEP at 0x%08x\n",
		     (unsigned) current_event.u.Exception.ExceptionRecord.ExceptionAddress));
      ourstatus->value.sig = TARGET_SIGNAL_TRAP;
      break;
    case EXCEPTION_ILLEGAL_INSTRUCTION:
      DEBUG_EXCEPT (("gdb: Target exception SINGLE_ILL at 0x%08x\n",
	       current_event.u.Exception.ExceptionRecord.ExceptionAddress));
      ourstatus->value.sig = check_for_step (&current_event, TARGET_SIGNAL_ILL);
      break;
    default:
      /* This may be a structured exception handling exception.  In
	 that case, we want to let the program try to handle it, and
	 only break if we see the exception a second time.  */

      printf_unfiltered ("gdb: unknown target exception 0x%08x at 0x%08x\n",
		    current_event.u.Exception.ExceptionRecord.ExceptionCode,
		current_event.u.Exception.ExceptionRecord.ExceptionAddress);
      ourstatus->value.sig = TARGET_SIGNAL_UNKNOWN;
      break;
    }
  exception_count++;
  return 1;
}