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
struct tui_gen_win_info {scalar_t__ type; } ;
struct tui_win_info {int /*<<< orphan*/  can_highlight; struct tui_gen_win_info generic; } ;
typedef  enum tui_win_type { ____Placeholder_tui_win_type } tui_win_type ;

/* Variables and functions */
 scalar_t__ CMD_WIN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  init_gen_win_info (struct tui_gen_win_info*,int,int,int,int,int) ; 
 scalar_t__ tui_alloc_generic_win_info () ; 
 scalar_t__ tui_alloc_win_info (int) ; 
 int /*<<< orphan*/  tui_make_window (struct tui_gen_win_info*,int) ; 
 scalar_t__ tui_win_is_auxillary (int) ; 

__attribute__((used)) static void
init_and_make_win (void ** win_info_ptr, enum tui_win_type win_type,
                 int height, int width, int origin_x, int origin_y, int box_it)
{
  void *opaque_win_info = *win_info_ptr;
  struct tui_gen_win_info * generic;

  if (opaque_win_info == NULL)
    {
      if (tui_win_is_auxillary (win_type))
	opaque_win_info = (void *) tui_alloc_generic_win_info ();
      else
	opaque_win_info = (void *) tui_alloc_win_info (win_type);
    }
  if (tui_win_is_auxillary (win_type))
    generic = (struct tui_gen_win_info *) opaque_win_info;
  else
    generic = &((struct tui_win_info *) opaque_win_info)->generic;

  if (opaque_win_info != NULL)
    {
      init_gen_win_info (generic, win_type, height, width, origin_x, origin_y);
      if (!tui_win_is_auxillary (win_type))
	{
	  if (generic->type == CMD_WIN)
	    ((struct tui_win_info *) opaque_win_info)->can_highlight = FALSE;
	  else
	    ((struct tui_win_info *) opaque_win_info)->can_highlight = TRUE;
	}
      tui_make_window (generic, box_it);
    }
  *win_info_ptr = opaque_win_info;
}