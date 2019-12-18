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
struct TYPE_2__ {int /*<<< orphan*/ * handle; } ;
struct tui_win_info {TYPE_1__ generic; } ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 unsigned int ERR ; 
#define  KEY_DOWN 135 
#define  KEY_LEFT 134 
#define  KEY_NPAGE 133 
#define  KEY_PPAGE 132 
#define  KEY_RIGHT 131 
#define  KEY_SF 130 
#define  KEY_SR 129 
#define  KEY_UP 128 
 struct tui_win_info* TUI_CMD_WIN ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  key_is_end_sequence (unsigned int) ; 
 scalar_t__ key_is_start_sequence (unsigned int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char toupper (char) ; 
 int /*<<< orphan*/  tui_refresh_all_win () ; 
 int /*<<< orphan*/  tui_scroll_backward (struct tui_win_info*,int) ; 
 int /*<<< orphan*/  tui_scroll_forward (struct tui_win_info*,int) ; 
 int /*<<< orphan*/  tui_scroll_left (struct tui_win_info*,int) ; 
 int /*<<< orphan*/  tui_scroll_right (struct tui_win_info*,int) ; 
 struct tui_win_info* tui_win_with_focus () ; 
 scalar_t__ wgetch (int /*<<< orphan*/ *) ; 

unsigned int
tui_dispatch_ctrl_char (unsigned int ch)
{
  struct tui_win_info *win_info = tui_win_with_focus ();
  WINDOW *w = TUI_CMD_WIN->generic.handle;

  /*
     ** If the command window has the logical focus, or no-one does
     ** assume it is the command window; in this case, pass the
     ** character on through and do nothing here.
   */
  if (win_info == NULL || win_info == TUI_CMD_WIN)
    return ch;
  else
    {
      unsigned int c = 0, ch_copy = ch;
      int i;
      char *term;

      /* If this is an xterm, page next/prev keys aren't returned
         ** by keypad as a single char, so we must handle them here.
         ** Seems like a bug in the curses library?
       */
      term = (char *) getenv ("TERM");
      for (i = 0; (term && term[i]); i++)
	term[i] = toupper (term[i]);
      if ((strcmp (term, "XTERM") == 0) && key_is_start_sequence (ch))
	{
	  unsigned int page_ch = 0;
	  unsigned int tmp_char;

	  tmp_char = 0;
	  while (!key_is_end_sequence (tmp_char))
	    {
	      tmp_char = (int) wgetch (w);
	      if (tmp_char == ERR)
		{
		  return ch;
		}
	      if (!tmp_char)
		break;
	      if (tmp_char == 53)
		page_ch = KEY_PPAGE;
	      else if (tmp_char == 54)
		page_ch = KEY_NPAGE;
	      else
		{
		  return 0;
		}
	    }
	  ch_copy = page_ch;
	}

      switch (ch_copy)
	{
	case KEY_NPAGE:
	  tui_scroll_forward (win_info, 0);
	  break;
	case KEY_PPAGE:
	  tui_scroll_backward (win_info, 0);
	  break;
	case KEY_DOWN:
	case KEY_SF:
	  tui_scroll_forward (win_info, 1);
	  break;
	case KEY_UP:
	case KEY_SR:
	  tui_scroll_backward (win_info, 1);
	  break;
	case KEY_RIGHT:
	  tui_scroll_left (win_info, 1);
	  break;
	case KEY_LEFT:
	  tui_scroll_right (win_info, 1);
	  break;
	case '\f':
	  tui_refresh_all_win ();
	  break;
	default:
	  c = ch_copy;
	  break;
	}
      return c;
    }
}