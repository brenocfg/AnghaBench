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
struct symtab_and_line {scalar_t__ end; } ;
struct sparc_frame_cache {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct symtab_and_line find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_pc_partial_function (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ sparc_analyze_prologue (scalar_t__,int,struct sparc_frame_cache*) ; 

__attribute__((used)) static CORE_ADDR
sparc64_skip_prologue (CORE_ADDR start_pc)
{
  struct symtab_and_line sal;
  CORE_ADDR func_start, func_end;
  struct sparc_frame_cache cache;

  /* This is the preferred method, find the end of the prologue by
     using the debugging information.  */
  if (find_pc_partial_function (start_pc, NULL, &func_start, &func_end))
    {
      sal = find_pc_line (func_start, 0);

      if (sal.end < func_end
	  && start_pc <= sal.end)
	return sal.end;
    }

  return sparc_analyze_prologue (start_pc, 0xffffffffffffffffULL, &cache);
}