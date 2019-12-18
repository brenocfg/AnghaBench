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
struct TYPE_2__ {int height; int /*<<< orphan*/  is_visible; } ;
struct tui_win_info {TYPE_1__ generic; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ TUI_FAILURE ; 
 int /*<<< orphan*/  WIN_HEIGHT_USAGE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  printf_filtered (int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 char toupper (char) ; 
 scalar_t__ tui_adjust_win_heights (struct tui_win_info*,int) ; 
 int /*<<< orphan*/  tui_enable () ; 
 struct tui_win_info* tui_partial_win_by_name (char*) ; 
 int /*<<< orphan*/  tui_update_gdb_sizes () ; 
 int /*<<< orphan*/  warning (char*,...) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
tui_set_win_height (char *arg, int from_tty)
{
  /* Make sure the curses mode is enabled.  */
  tui_enable ();
  if (arg != (char *) NULL)
    {
      char *buf = xstrdup (arg);
      char *buf_ptr = buf;
      char *wname = (char *) NULL;
      int new_height, i;
      struct tui_win_info * win_info;

      wname = buf_ptr;
      buf_ptr = strchr (buf_ptr, ' ');
      if (buf_ptr != (char *) NULL)
	{
	  *buf_ptr = (char) 0;

	  /*
	     ** Validate the window name
	   */
	  for (i = 0; i < strlen (wname); i++)
	    wname[i] = toupper (wname[i]);
	  win_info = tui_partial_win_by_name (wname);

	  if (win_info == (struct tui_win_info *) NULL || !win_info->generic.is_visible)
	    warning ("Invalid window specified. \n\
The window name specified must be valid and visible.\n");
	  else
	    {
	      /* Process the size */
	      while (*(++buf_ptr) == ' ')
		;

	      if (*buf_ptr != (char) 0)
		{
		  int negate = FALSE;
		  int fixed_size = TRUE;
		  int input_no;;

		  if (*buf_ptr == '+' || *buf_ptr == '-')
		    {
		      if (*buf_ptr == '-')
			negate = TRUE;
		      fixed_size = FALSE;
		      buf_ptr++;
		    }
		  input_no = atoi (buf_ptr);
		  if (input_no > 0)
		    {
		      if (negate)
			input_no *= (-1);
		      if (fixed_size)
			new_height = input_no;
		      else
			new_height = win_info->generic.height + input_no;
		      /*
		         ** Now change the window's height, and adjust all
		         ** other windows around it
		       */
		      if (tui_adjust_win_heights (win_info,
						new_height) == TUI_FAILURE)
			warning ("Invalid window height specified.\n%s",
				 WIN_HEIGHT_USAGE);
		      else
                        tui_update_gdb_sizes ();
		    }
		  else
		    warning ("Invalid window height specified.\n%s",
			     WIN_HEIGHT_USAGE);
		}
	    }
	}
      else
	printf_filtered (WIN_HEIGHT_USAGE);

      if (buf != (char *) NULL)
	xfree (buf);
    }
  else
    printf_filtered (WIN_HEIGHT_USAGE);
}