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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  tui_set_win_resized_to (int /*<<< orphan*/ ) ; 

void
tui_sigwinch_handler (int signal)
{
  /*
     ** Say that a resize was done so that the readline can do it
     ** later when appropriate.
   */
  tui_set_win_resized_to (TRUE);
}