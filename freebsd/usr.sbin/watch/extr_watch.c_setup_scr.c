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
 int /*<<< orphan*/  clear () ; 
 int clear_ok ; 
 char* gbuf ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  opt_interactive ; 
 int /*<<< orphan*/  set_tty () ; 
 int /*<<< orphan*/  tbuf ; 
 int tgetent (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tgetstr (char*,char**) ; 

__attribute__((used)) static void
setup_scr(void)
{
	char		*cbuf = gbuf, *term;

	if (!opt_interactive)
		return;
	if ((term = getenv("TERM")))
		if (tgetent(tbuf, term) == 1)
			if (tgetstr("cl", &cbuf))
				clear_ok = 1;
	set_tty();
	clear();
}