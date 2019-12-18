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
 int cngetc () ; 
 int /*<<< orphan*/  cnputc (char) ; 
 int /*<<< orphan*/  db_capture_enterpager () ; 
 int /*<<< orphan*/  db_capture_exitpager () ; 
 int /*<<< orphan*/  db_force_whitespace () ; 
 int db_lines_per_page ; 
 int db_maxlines ; 
 scalar_t__ db_newlines ; 
 int db_pager_quit ; 
 int /*<<< orphan*/  db_printf (char*) ; 

void
db_pager(void)
{
	int c, done;

	db_capture_enterpager();
	db_printf("--More--\r");
	done = 0;
	while (!done) {
		c = cngetc();
		switch (c) {
		case 'e':
		case 'j':
		case '\n':
			/* Just one more line. */
			db_maxlines = 1;
			done++;
			break;
		case 'd':
			/* Half a page. */
			db_maxlines = db_lines_per_page / 2;
			done++;
			break;
		case 'f':
		case ' ':
			/* Another page. */
			db_maxlines = db_lines_per_page;
			done++;
			break;
		case 'q':
		case 'Q':
		case 'x':
		case 'X':
			/* Quit */
			db_maxlines = 0;
			db_pager_quit = 1;
			done++;
			break;
#if 0
			/* FALLTHROUGH */
		default:
			cnputc('\007');
#endif
		}
	}
	db_printf("        ");
	db_force_whitespace();
	db_printf("\r");
	db_newlines = 0;
	db_capture_exitpager();
}