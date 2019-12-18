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
struct tui_win_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORWARD_SCROLL ; 
 int /*<<< orphan*/  parse_scrolling_args (char*,struct tui_win_info**,int*) ; 
 int /*<<< orphan*/  tui_enable () ; 
 int /*<<< orphan*/  tui_scroll (int /*<<< orphan*/ ,struct tui_win_info*,int) ; 

__attribute__((used)) static void
tui_scroll_forward_command (char *arg, int from_tty)
{
  int num_to_scroll = 1;
  struct tui_win_info * win_to_scroll;

  /* Make sure the curses mode is enabled.  */
  tui_enable ();
  if (arg == (char *) NULL)
    parse_scrolling_args (arg, &win_to_scroll, (int *) NULL);
  else
    parse_scrolling_args (arg, &win_to_scroll, &num_to_scroll);
  tui_scroll (FORWARD_SCROLL, win_to_scroll, num_to_scroll);
}