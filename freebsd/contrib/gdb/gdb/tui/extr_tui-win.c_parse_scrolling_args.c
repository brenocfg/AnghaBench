#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  is_visible; } ;
struct tui_win_info {TYPE_1__ generic; } ;
struct TYPE_4__ {scalar_t__* list; } ;

/* Variables and functions */
 struct tui_win_info* TUI_CMD_WIN ; 
 int atoi (char*) ; 
 scalar_t__ isdigit (char) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 char toupper (char) ; 
 struct tui_win_info* tui_partial_win_by_name (char*) ; 
 TYPE_2__* tui_source_windows () ; 
 struct tui_win_info* tui_win_with_focus () ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
parse_scrolling_args (char *arg, struct tui_win_info * * win_to_scroll,
		      int *num_to_scroll)
{
  if (num_to_scroll)
    *num_to_scroll = 0;
  *win_to_scroll = tui_win_with_focus ();

  /*
     ** First set up the default window to scroll, in case there is no
     ** window name arg
   */
  if (arg != (char *) NULL)
    {
      char *buf, *buf_ptr;

      /* process the number of lines to scroll */
      buf = buf_ptr = xstrdup (arg);
      if (isdigit (*buf_ptr))
	{
	  char *num_str;

	  num_str = buf_ptr;
	  buf_ptr = strchr (buf_ptr, ' ');
	  if (buf_ptr != (char *) NULL)
	    {
	      *buf_ptr = (char) 0;
	      if (num_to_scroll)
		*num_to_scroll = atoi (num_str);
	      buf_ptr++;
	    }
	  else if (num_to_scroll)
	    *num_to_scroll = atoi (num_str);
	}

      /* process the window name if one is specified */
      if (buf_ptr != (char *) NULL)
	{
	  char *wname;
	  int i;

	  if (*buf_ptr == ' ')
	    while (*(++buf_ptr) == ' ')
	      ;

	  if (*buf_ptr != (char) 0)
	    wname = buf_ptr;
	  else
	    wname = "?";
	  
	  /* Validate the window name */
	  for (i = 0; i < strlen (wname); i++)
	    wname[i] = toupper (wname[i]);
	  *win_to_scroll = tui_partial_win_by_name (wname);

	  if (*win_to_scroll == (struct tui_win_info *) NULL ||
	      !(*win_to_scroll)->generic.is_visible)
	    warning ("Invalid window specified. \n\
The window name specified must be valid and visible.\n");
	  else if (*win_to_scroll == TUI_CMD_WIN)
	    *win_to_scroll = (struct tui_win_info *) (tui_source_windows ())->list[0];
	}
      xfree (buf);
    }
}