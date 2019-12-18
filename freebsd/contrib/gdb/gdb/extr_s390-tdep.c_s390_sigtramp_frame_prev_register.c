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
struct s390_sigtramp_unwind_cache {int /*<<< orphan*/  saved_regs; } ;
struct frame_info {int dummy; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct s390_sigtramp_unwind_cache* s390_sigtramp_frame_unwind_cache (struct frame_info*,void**) ; 
 int /*<<< orphan*/  trad_frame_prev_register (struct frame_info*,int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ *,int*,void*) ; 

__attribute__((used)) static void
s390_sigtramp_frame_prev_register (struct frame_info *next_frame,
				   void **this_prologue_cache,
				   int regnum, int *optimizedp,
				   enum lval_type *lvalp, CORE_ADDR *addrp,
				   int *realnump, void *bufferp)
{
  struct s390_sigtramp_unwind_cache *info
    = s390_sigtramp_frame_unwind_cache (next_frame, this_prologue_cache);
  trad_frame_prev_register (next_frame, info->saved_regs, regnum,
                            optimizedp, lvalp, addrp, realnump, bufferp);
}