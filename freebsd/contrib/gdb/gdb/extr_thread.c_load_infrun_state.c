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
struct thread_info {int trap_expected; int handling_longjmp; int another_trap; int stepping_through_solib_after_catch; int stepping_through_sigtramp; int current_line; int /*<<< orphan*/  step_sp; struct symtab* current_symtab; int /*<<< orphan*/  stepping_through_solib_catchpoints; struct frame_id step_frame_id; int /*<<< orphan*/  step_range_end; int /*<<< orphan*/  step_range_start; struct breakpoint* through_sigtramp_breakpoint; struct breakpoint* step_resume_breakpoint; int /*<<< orphan*/  prev_pc; } ;
struct symtab {int dummy; } ;
struct breakpoint {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int /*<<< orphan*/  bpstat ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct thread_info* find_thread_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_to_thread_id (int /*<<< orphan*/ ) ; 

void
load_infrun_state (ptid_t ptid,
		   CORE_ADDR *prev_pc,
		   int *trap_expected,
		   struct breakpoint **step_resume_breakpoint,
		   struct breakpoint **through_sigtramp_breakpoint,
		   CORE_ADDR *step_range_start,
		   CORE_ADDR *step_range_end,
		   struct frame_id *step_frame_id,
		   int *handling_longjmp,
		   int *another_trap,
		   int *stepping_through_solib_after_catch,
		   bpstat *stepping_through_solib_catchpoints,
		   int *stepping_through_sigtramp,
		   int *current_line,
		   struct symtab **current_symtab, CORE_ADDR *step_sp)
{
  struct thread_info *tp;

  /* If we can't find the thread, then we're debugging a single threaded
     process.  No need to do anything in that case.  */
  tp = find_thread_id (pid_to_thread_id (ptid));
  if (tp == NULL)
    return;

  *prev_pc = tp->prev_pc;
  *trap_expected = tp->trap_expected;
  *step_resume_breakpoint = tp->step_resume_breakpoint;
  *through_sigtramp_breakpoint = tp->through_sigtramp_breakpoint;
  *step_range_start = tp->step_range_start;
  *step_range_end = tp->step_range_end;
  *step_frame_id = tp->step_frame_id;
  *handling_longjmp = tp->handling_longjmp;
  *another_trap = tp->another_trap;
  *stepping_through_solib_after_catch =
    tp->stepping_through_solib_after_catch;
  *stepping_through_solib_catchpoints =
    tp->stepping_through_solib_catchpoints;
  *stepping_through_sigtramp = tp->stepping_through_sigtramp;
  *current_line = tp->current_line;
  *current_symtab = tp->current_symtab;
  *step_sp = tp->step_sp;
}