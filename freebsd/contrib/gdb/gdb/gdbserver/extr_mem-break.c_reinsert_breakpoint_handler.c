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
struct breakpoint {scalar_t__ reinserting; int /*<<< orphan*/  pc; struct breakpoint* breakpoint_to_reinsert; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_memory ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  breakpoint_data ; 
 int /*<<< orphan*/  breakpoint_len ; 
 int /*<<< orphan*/  delete_breakpoint (struct breakpoint*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct breakpoint* find_breakpoint_at (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* the_target ; 

__attribute__((used)) static void
reinsert_breakpoint_handler (CORE_ADDR stop_pc)
{
  struct breakpoint *stop_bp, *orig_bp;

  stop_bp = find_breakpoint_at (stop_pc);
  if (stop_bp == NULL)
    error ("lost the stopping breakpoint.");

  orig_bp = stop_bp->breakpoint_to_reinsert;
  if (orig_bp == NULL)
    error ("no breakpoint to reinsert");

  (*the_target->write_memory) (orig_bp->pc, breakpoint_data,
			       breakpoint_len);
  orig_bp->reinserting = 0;
  delete_breakpoint (stop_bp);
}