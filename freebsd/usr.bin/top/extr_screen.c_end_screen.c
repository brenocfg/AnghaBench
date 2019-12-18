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
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  clear_line ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ is_a_terminal ; 
 int /*<<< orphan*/  lower_left ; 
 int /*<<< orphan*/  old_settings ; 
 int /*<<< orphan*/  putcap (int /*<<< orphan*/ ) ; 
 scalar_t__ smart_terminal ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminal_end ; 

void
end_screen(void)
{
    /* move to the lower left, clear the line and send "te" */
    if (smart_terminal)
    {
	putcap(lower_left);
	putcap(clear_line);
	fflush(stdout);
	putcap(terminal_end);
    }

    /* if we have settings to reset, then do so */
    if (is_a_terminal)
    {
	tcsetattr(STDOUT_FILENO, TCSADRAIN, &old_settings);
    }
}