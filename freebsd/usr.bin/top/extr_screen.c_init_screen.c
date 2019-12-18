#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int c_lflag; int* c_cc; int /*<<< orphan*/  c_oflag; } ;

/* Variables and functions */
 int ECHO ; 
 int ICANON ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TAB3 ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 size_t VERASE ; 
 size_t VKILL ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int ch_erase ; 
 int ch_kill ; 
 int is_a_terminal ; 
 TYPE_1__ new_settings ; 
 TYPE_1__ old_settings ; 
 int /*<<< orphan*/  putcap (int /*<<< orphan*/ ) ; 
 int smart_terminal ; 
 int tcgetattr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  terminal_init ; 

void
init_screen(void)
{
    /* get the old settings for safe keeping */
    if (tcgetattr(STDOUT_FILENO, &old_settings) != -1)
    {
	/* copy the settings so we can modify them */
	new_settings = old_settings;

	/* turn off ICANON, character echo and tab expansion */
	new_settings.c_lflag &= ~(ICANON|ECHO);
	new_settings.c_oflag &= ~(TAB3);
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	tcsetattr(STDOUT_FILENO, TCSADRAIN, &new_settings);

	/* remember the erase and kill characters */
	ch_erase = old_settings.c_cc[VERASE];
	ch_kill  = old_settings.c_cc[VKILL];

	/* remember that it really is a terminal */
	is_a_terminal = true;

	/* send the termcap initialization string */
	putcap(terminal_init);
    }

    if (!is_a_terminal)
    {
	/* not a terminal at all---consider it dumb */
	smart_terminal = false;
    }
}