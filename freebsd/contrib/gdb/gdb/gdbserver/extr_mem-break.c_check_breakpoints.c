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
struct breakpoint {int /*<<< orphan*/  pc; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;scalar_t__ reinserting; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct breakpoint* find_breakpoint_at (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*) ; 

int
check_breakpoints (CORE_ADDR stop_pc)
{
  struct breakpoint *bp;

  bp = find_breakpoint_at (stop_pc);
  if (bp == NULL)
    return 0;
  if (bp->reinserting)
    {
      warning ("Hit a removed breakpoint?");
      return 0;
    }

  (*bp->handler) (bp->pc);
  return 1;
}