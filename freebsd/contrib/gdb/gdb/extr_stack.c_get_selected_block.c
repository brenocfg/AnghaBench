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
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct block* block_for_pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 struct block* get_frame_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_pc () ; 
 int /*<<< orphan*/  target_has_stack ; 

struct block *
get_selected_block (CORE_ADDR *addr_in_block)
{
  if (!target_has_stack)
    return 0;

  /* NOTE: cagney/2002-11-28: Why go to all this effort to not create
     a selected/current frame?  Perhaphs this function is called,
     indirectly, by WFI in "infrun.c" where avoiding the creation of
     an inner most frame is very important (it slows down single
     step).  I suspect, though that this was true in the deep dark
     past but is no longer the case.  A mindless look at all the
     callers tends to support this theory.  I think we should be able
     to assume that there is always a selcted frame.  */
  /* gdb_assert (deprecated_selected_frame != NULL); So, do you feel
     lucky? */
  if (!deprecated_selected_frame)
    {
      CORE_ADDR pc = read_pc ();
      if (addr_in_block != NULL)
	*addr_in_block = pc;
      return block_for_pc (pc);
    }
  return get_frame_block (deprecated_selected_frame, addr_in_block);
}