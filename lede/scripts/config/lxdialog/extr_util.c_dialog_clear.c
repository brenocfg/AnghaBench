#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct subtitle_list {char const* text; struct subtitle_list* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  atr; } ;
struct TYPE_4__ {struct subtitle_list* subtitles; int /*<<< orphan*/ * backtitle; TYPE_1__ screen; } ;

/* Variables and functions */
 char ACS_HLINE ; 
 char ACS_RARROW ; 
 int /*<<< orphan*/  attr_clear (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ dlg ; 
 int getmaxx (int /*<<< orphan*/ ) ; 
 int getmaxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwaddstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  stdscr ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ ) ; 

void dialog_clear(void)
{
	int lines, columns;

	lines = getmaxy(stdscr);
	columns = getmaxx(stdscr);

	attr_clear(stdscr, lines, columns, dlg.screen.atr);
	/* Display background title if it exists ... - SLH */
	if (dlg.backtitle != NULL) {
		int i, len = 0, skip = 0;
		struct subtitle_list *pos;

		wattrset(stdscr, dlg.screen.atr);
		mvwaddstr(stdscr, 0, 1, (char *)dlg.backtitle);

		for (pos = dlg.subtitles; pos != NULL; pos = pos->next) {
			/* 3 is for the arrow and spaces */
			len += strlen(pos->text) + 3;
		}

		wmove(stdscr, 1, 1);
		if (len > columns - 2) {
			const char *ellipsis = "[...] ";
			waddstr(stdscr, ellipsis);
			skip = len - (columns - 2 - strlen(ellipsis));
		}

		for (pos = dlg.subtitles; pos != NULL; pos = pos->next) {
			if (skip == 0)
				waddch(stdscr, ACS_RARROW);
			else
				skip--;

			if (skip == 0)
				waddch(stdscr, ' ');
			else
				skip--;

			if (skip < strlen(pos->text)) {
				waddstr(stdscr, pos->text + skip);
				skip = 0;
			} else
				skip -= strlen(pos->text);

			if (skip == 0)
				waddch(stdscr, ' ');
			else
				skip--;
		}

		for (i = len + 1; i < columns - 1; i++)
			waddch(stdscr, ACS_HLINE);
	}
	wnoutrefresh(stdscr);
}