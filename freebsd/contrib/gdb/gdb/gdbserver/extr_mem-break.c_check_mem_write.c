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
struct breakpoint {scalar_t__ pc; char* old_data; scalar_t__ reinserting; struct breakpoint* next; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 char* breakpoint_data ; 
 scalar_t__ breakpoint_len ; 
 struct breakpoint* breakpoints ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

void
check_mem_write (CORE_ADDR mem_addr, char *buf, int mem_len)
{
  struct breakpoint *bp = breakpoints;
  CORE_ADDR mem_end = mem_addr + mem_len;

  for (; bp != NULL; bp = bp->next)
    {
      CORE_ADDR bp_end = bp->pc + breakpoint_len;
      CORE_ADDR start, end;
      int copy_offset, copy_len, buf_offset;

      if (mem_addr >= bp_end)
	continue;
      if (bp->pc >= mem_end)
	continue;

      start = bp->pc;
      if (mem_addr > start)
	start = mem_addr;

      end = bp_end;
      if (end > mem_end)
	end = mem_end;

      copy_len = end - start;
      copy_offset = start - bp->pc;
      buf_offset = start - mem_addr;

      memcpy (bp->old_data + copy_offset, buf + buf_offset, copy_len);
      if (bp->reinserting == 0)
	memcpy (buf + buf_offset, breakpoint_data + copy_offset, copy_len);
    }
}