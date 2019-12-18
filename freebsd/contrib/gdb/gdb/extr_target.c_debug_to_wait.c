#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sig; int /*<<< orphan*/  integer; } ;
struct target_waitstatus {int kind; TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* to_wait ) (int /*<<< orphan*/ ,struct target_waitstatus*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
#define  TARGET_WAITKIND_EXECD 135 
#define  TARGET_WAITKIND_EXITED 134 
#define  TARGET_WAITKIND_FORKED 133 
#define  TARGET_WAITKIND_LOADED 132 
#define  TARGET_WAITKIND_SIGNALLED 131 
#define  TARGET_WAITKIND_SPURIOUS 130 
#define  TARGET_WAITKIND_STOPPED 129 
#define  TARGET_WAITKIND_VFORKED 128 
 TYPE_2__ debug_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct target_waitstatus*) ; 
 int /*<<< orphan*/  target_signal_to_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ptid_t
debug_to_wait (ptid_t ptid, struct target_waitstatus *status)
{
  ptid_t retval;

  retval = debug_target.to_wait (ptid, status);

  fprintf_unfiltered (gdb_stdlog,
		      "target_wait (%d, status) = %d,   ", PIDGET (ptid),
		      PIDGET (retval));
  fprintf_unfiltered (gdb_stdlog, "status->kind = ");
  switch (status->kind)
    {
    case TARGET_WAITKIND_EXITED:
      fprintf_unfiltered (gdb_stdlog, "exited, status = %d\n",
			  status->value.integer);
      break;
    case TARGET_WAITKIND_STOPPED:
      fprintf_unfiltered (gdb_stdlog, "stopped, signal = %s\n",
			  target_signal_to_name (status->value.sig));
      break;
    case TARGET_WAITKIND_SIGNALLED:
      fprintf_unfiltered (gdb_stdlog, "signalled, signal = %s\n",
			  target_signal_to_name (status->value.sig));
      break;
    case TARGET_WAITKIND_LOADED:
      fprintf_unfiltered (gdb_stdlog, "loaded\n");
      break;
    case TARGET_WAITKIND_FORKED:
      fprintf_unfiltered (gdb_stdlog, "forked\n");
      break;
    case TARGET_WAITKIND_VFORKED:
      fprintf_unfiltered (gdb_stdlog, "vforked\n");
      break;
    case TARGET_WAITKIND_EXECD:
      fprintf_unfiltered (gdb_stdlog, "execd\n");
      break;
    case TARGET_WAITKIND_SPURIOUS:
      fprintf_unfiltered (gdb_stdlog, "spurious\n");
      break;
    default:
      fprintf_unfiltered (gdb_stdlog, "unknown???\n");
      break;
    }

  return retval;
}