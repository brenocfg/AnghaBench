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

/* Variables and functions */
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  SIGWINCH_HANDLER (int /*<<< orphan*/ ) ; 
 int ScreenCols () ; 
 int ScreenRows () ; 
 int UINT_MAX ; 
 int chars_per_line ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ getenv (char*) ; 
 int lines_per_page ; 
 int /*<<< orphan*/  rl_get_screen_size (int*,int*) ; 
 int /*<<< orphan*/  rl_reset_terminal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_screen_size () ; 
 int /*<<< orphan*/  set_width () ; 
 scalar_t__ tgetnum (char*) ; 
 int /*<<< orphan*/  tui_get_command_dimension (int*,int*) ; 
 int /*<<< orphan*/  ui_file_isatty (int /*<<< orphan*/ ) ; 

void
init_page_info (void)
{
#if defined(TUI)
  if (!tui_get_command_dimension (&chars_per_line, &lines_per_page))
#endif
    {
      int rows, cols;

#if defined(__GO32__)
      rows = ScreenRows ();
      cols = ScreenCols ();
      lines_per_page = rows;
      chars_per_line = cols;
#else
      /* Make sure Readline has initialized its terminal settings.  */
      rl_reset_terminal (NULL);

      /* Get the screen size from Readline.  */
      rl_get_screen_size (&rows, &cols);
      lines_per_page = rows;
      chars_per_line = cols;

      /* Readline should have fetched the termcap entry for us.  */
      if (tgetnum ("li") < 0 || getenv ("EMACS"))
	{
	  /* The number of lines per page is not mentioned in the
	     terminal description.  This probably means that paging is
	     not useful (e.g. emacs shell window), so disable paging.  */
	  lines_per_page = UINT_MAX;
	}

      /* FIXME: Get rid of this junk.  */
#if defined(SIGWINCH) && defined(SIGWINCH_HANDLER)
      SIGWINCH_HANDLER (SIGWINCH);
#endif

      /* If the output is not a terminal, don't paginate it.  */
      if (!ui_file_isatty (gdb_stdout))
	lines_per_page = UINT_MAX;
#endif
    }

  set_screen_size ();
  set_width ();
}