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
struct breakpoint {scalar_t__ pc; struct breakpoint* next; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct breakpoint* breakpoints ; 

__attribute__((used)) static struct breakpoint *
find_breakpoint_at (CORE_ADDR where)
{
  struct breakpoint *bp = breakpoints;

  while (bp != NULL)
    {
      if (bp->pc == where)
	return bp;
      bp = bp->next;
    }

  return NULL;
}