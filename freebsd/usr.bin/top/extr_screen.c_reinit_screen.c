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
 scalar_t__ is_a_terminal ; 
 int /*<<< orphan*/  new_settings ; 
 int /*<<< orphan*/  putcap (int /*<<< orphan*/ ) ; 
 scalar_t__ smart_terminal ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminal_init ; 

void
reinit_screen(void)
{
    /* install our settings if it is a terminal */
    if (is_a_terminal)
    {
	tcsetattr(STDOUT_FILENO, TCSADRAIN, &new_settings);
    }

    /* send init string */
    if (smart_terminal)
    {
	putcap(terminal_init);
    }
}