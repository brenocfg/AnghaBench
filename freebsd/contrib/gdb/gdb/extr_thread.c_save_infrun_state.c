#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct frame_id {int dummy; } ;
struct thread_info {int trap_expected; int handling_longjmp; int another_trap; int stepping_through_solib_after_catch; int stepping_through_sigtramp; int current_line; void* step_sp; struct symtab* current_symtab; int /*<<< orphan*/  stepping_through_solib_catchpoints; struct frame_id step_frame_id; void* step_range_end; void* step_range_start; struct breakpoint* through_sigtramp_breakpoint; struct breakpoint* step_resume_breakpoint; void* prev_pc; } ;
struct symtab {int dummy; } ;
struct breakpoint {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int /*<<< orphan*/  bpstat ;
typedef  void* CORE_ADDR ;

/* Variables and functions */
 struct thread_info* find_thread_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_to_thread_id (int /*<<< orphan*/ ) ; 

void
save_infrun_state (ptid_t ptid,
		   CORE_ADDR prev_pc,
		   int trap_expected,
		   struct breakpoint *step_resume_breakpoint,
		   struct breakpoint *through_sigtramp_breakpoint,
		   CORE_ADDR step_range_start,
		   CORE_ADDR step_range_end,
		   const struct frame_id *step_frame_id,
		   int handling_longjmp,
		   int another_trap,
		   int stepping_through_solib_after_catch,
		   bpstat stepping_through_solib_catchpoints,
		   int stepping_through_sigtramp,
		   int current_line,
		   struct symtab *current_symtab, CORE_ADDR step_sp)
{
  struct thread_info *tp;

  /* If we can't find the thread, then we're debugging a single-threaded
     process.  Nothing to do in that case.  */
  tp = find_thread_id (pid_to_thread_id (ptid));
  if (tp == NULL)
    return;

  tp->prev_pc = prev_pc;
  tp->trap_expected = trap_expected;
  tp->step_resume_breakpoint = step_resume_breakpoint;
  tp->through_sigtramp_breakpoint = through_sigtramp_breakpoint;
  tp->step_range_start = step_range_start;
  tp->step_range_end = step_range_end;
  tp->step_frame_id = (*step_frame_id);
  tp->handling_longjmp = handling_longjmp;
  tp->another_trap = another_trap;
  tp->stepping_through_solib_after_catch = stepping_through_solib_after_catch;
  tp->stepping_through_solib_catchpoints = stepping_through_solib_catchpoints;
  tp->stepping_through_sigtramp = stepping_through_sigtramp;
  tp->current_line = current_line;
  tp->current_symtab = current_symtab;
  tp->step_sp = step_sp;
}