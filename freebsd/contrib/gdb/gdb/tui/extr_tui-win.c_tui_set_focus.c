#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  is_visible; } ;
struct tui_win_info {TYPE_1__ generic; } ;
struct tui_gen_win_info {int dummy; } ;
struct TYPE_5__ {scalar_t__ is_visible; } ;
struct TYPE_6__ {TYPE_2__ generic; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOCUS_USAGE ; 
 struct tui_win_info* TUI_CMD_WIN ; 
 TYPE_3__* TUI_DATA_WIN ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ subset_compare (char*,char*) ; 
 char toupper (char) ; 
 struct tui_win_info* tui_next_win (scalar_t__) ; 
 struct tui_win_info* tui_partial_win_by_name (char*) ; 
 struct tui_win_info* tui_prev_win (scalar_t__) ; 
 int /*<<< orphan*/  tui_refresh_data_win () ; 
 int /*<<< orphan*/  tui_set_win_focus_to (struct tui_win_info*) ; 
 int /*<<< orphan*/  tui_win_name (struct tui_gen_win_info*) ; 
 scalar_t__ tui_win_with_focus () ; 
 int /*<<< orphan*/  warning (char*,...) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xstrdup (char*) ; 

__attribute__((used)) static void
tui_set_focus (char *arg, int from_tty)
{
  if (arg != (char *) NULL)
    {
      char *buf_ptr = (char *) xstrdup (arg);
      int i;
      struct tui_win_info * win_info = (struct tui_win_info *) NULL;

      for (i = 0; (i < strlen (buf_ptr)); i++)
	buf_ptr[i] = toupper (arg[i]);

      if (subset_compare (buf_ptr, "NEXT"))
	win_info = tui_next_win (tui_win_with_focus ());
      else if (subset_compare (buf_ptr, "PREV"))
	win_info = tui_prev_win (tui_win_with_focus ());
      else
	win_info = tui_partial_win_by_name (buf_ptr);

      if (win_info == (struct tui_win_info *) NULL || !win_info->generic.is_visible)
	warning ("Invalid window specified. \n\
The window name specified must be valid and visible.\n");
      else
	{
	  tui_set_win_focus_to (win_info);
	  keypad (TUI_CMD_WIN->generic.handle, (win_info != TUI_CMD_WIN));
	}

      if (TUI_DATA_WIN && TUI_DATA_WIN->generic.is_visible)
	tui_refresh_data_win ();
      xfree (buf_ptr);
      printf_filtered ("Focus set to %s window.\n",
		       tui_win_name ((struct tui_gen_win_info *) tui_win_with_focus ()));
    }
  else
    warning ("Incorrect Number of Arguments.\n%s", FOCUS_USAGE);
}