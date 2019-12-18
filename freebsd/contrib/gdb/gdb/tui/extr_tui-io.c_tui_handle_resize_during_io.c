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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  tui_refresh_all_win () ; 
 int /*<<< orphan*/  tui_set_win_resized_to (int /*<<< orphan*/ ) ; 
 scalar_t__ tui_win_resized () ; 

__attribute__((used)) static unsigned int
tui_handle_resize_during_io (unsigned int original_ch)
{
  if (tui_win_resized ())
    {
      tui_refresh_all_win ();
      dont_repeat ();
      tui_set_win_resized_to (FALSE);
      return '\n';
    }
  else
    return original_ch;
}