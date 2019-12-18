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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_terminal_dumb () ; 
 int /*<<< orphan*/  stderr ; 
 char* term_columns () ; 

void term_clear_line(void)
{
	if (is_terminal_dumb())
		/*
		 * Fall back to print a terminal width worth of space
		 * characters (hoping that the terminal is still as wide
		 * as it was upon the first call to term_columns()).
		 */
		fprintf(stderr, "\r%*s\r", term_columns(), "");
	else
		/*
		 * On non-dumb terminals use an escape sequence to clear
		 * the whole line, no matter how wide the terminal.
		 */
		fputs("\r\033[K", stderr);
}