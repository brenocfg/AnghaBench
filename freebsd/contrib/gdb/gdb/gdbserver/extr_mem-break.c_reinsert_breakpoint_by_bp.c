#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct breakpoint {int reinserting; int /*<<< orphan*/  old_data; int /*<<< orphan*/  pc; struct breakpoint* breakpoint_to_reinsert; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_memory ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  breakpoint_len ; 
 int /*<<< orphan*/  error (char*) ; 
 struct breakpoint* find_breakpoint_at (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinsert_breakpoint_handler ; 
 int /*<<< orphan*/  set_breakpoint_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* the_target ; 

void
reinsert_breakpoint_by_bp (CORE_ADDR stop_pc, CORE_ADDR stop_at)
{
  struct breakpoint *bp, *orig_bp;

  set_breakpoint_at (stop_at, reinsert_breakpoint_handler);

  orig_bp = find_breakpoint_at (stop_pc);
  if (orig_bp == NULL)
    error ("Could not find original breakpoint in list.");

  bp = find_breakpoint_at (stop_at);
  if (bp == NULL)
    error ("Could not find breakpoint in list (reinserting by breakpoint).");
  bp->breakpoint_to_reinsert = orig_bp;

  (*the_target->write_memory) (orig_bp->pc, orig_bp->old_data,
			       breakpoint_len);
  orig_bp->reinserting = 1;
}