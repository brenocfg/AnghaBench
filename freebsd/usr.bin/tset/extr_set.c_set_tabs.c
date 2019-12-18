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
 int Columns ; 
 int Lines ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  outc ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* tgetstr (char*,char**) ; 
 char* tgoto (char*,int,int) ; 
 int /*<<< orphan*/  tputs (char const*,int,int /*<<< orphan*/ ) ; 

int
set_tabs(void)
{
	int c;
	char *capsp, *clear_tabs;
	char *set_column, *set_pos, *Set_tab;
	char caps[1024];
	const char *tg_out;

	capsp = caps;
	Set_tab = tgetstr("st", &capsp);

	if (Set_tab && (clear_tabs = tgetstr("ct", &capsp))) {
		(void)putc('\r', stderr);	/* Force to left margin. */
		tputs(clear_tabs, 0, outc);
	}

	set_column = tgetstr("ch", &capsp);
	set_pos = set_column ? NULL : tgetstr("cm", &capsp);

	if (Set_tab) {
		for (c = 8; c < Columns; c += 8) {
			/*
			 * Get to the right column.  "OOPS" is returned by
			 * tgoto() if it can't do the job.  (*snarl*)
			 */
			tg_out = "OOPS";
			if (set_column)
				tg_out = tgoto(set_column, 0, c);
			if (*tg_out == 'O' && set_pos)
				tg_out = tgoto(set_pos, c, Lines - 1);
			if (*tg_out != 'O')
				tputs(tg_out, 1, outc);
			else
				(void)fprintf(stderr, "%s", "        ");
			/* Set the tab. */
			tputs(Set_tab, 0, outc);
		}
		putc('\r', stderr);
		return (1);
	}
	return (0);
}