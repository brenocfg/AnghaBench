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
 scalar_t__ NEXT_TAB (scalar_t__) ; 
 int /*<<< orphan*/  cnputc (int) ; 
 int /*<<< orphan*/  db_capture_writech (int) ; 
 int /*<<< orphan*/  db_check_interrupt () ; 
 int /*<<< orphan*/  db_force_whitespace () ; 
 scalar_t__ db_last_non_space ; 
 scalar_t__ db_maxlines ; 
 scalar_t__ db_newlines ; 
 scalar_t__ db_output_position ; 
 int /*<<< orphan*/  db_pager () ; 
 scalar_t__ ddb_use_printf ; 
 int /*<<< orphan*/  kdb_active ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
db_putc(int c)
{

	/*
	 * If not in the debugger or the user requests it, output data to
	 * both the console and the message buffer.
	 */
	if (!kdb_active || ddb_use_printf) {
		printf("%c", c);
		if (!kdb_active)
			return;
		if (c == '\r' || c == '\n')
			db_check_interrupt();
		if (c == '\n' && db_maxlines > 0) {
			db_newlines++;
			if (db_newlines >= db_maxlines)
				db_pager();
		}
		return;
	}

	/* Otherwise, output data directly to the console. */
	if (c > ' ' && c <= '~') {
	    /*
	     * Printing character.
	     * If we have spaces to print, print them first.
	     * Use tabs if possible.
	     */
	    db_force_whitespace();
	    cnputc(c);
	    db_capture_writech(c);
	    db_output_position++;
	    db_last_non_space = db_output_position;
	}
	else if (c == '\n') {
	    /* Newline */
	    cnputc(c);
	    db_capture_writech(c);
	    db_output_position = 0;
	    db_last_non_space = 0;
	    db_check_interrupt();
	    if (db_maxlines > 0) {
		    db_newlines++;
		    if (db_newlines >= db_maxlines)
			    db_pager();
	    }
	}
	else if (c == '\r') {
	    /* Return */
	    cnputc(c);
	    db_capture_writech(c);
	    db_output_position = 0;
	    db_last_non_space = 0;
	    db_check_interrupt();
	}
	else if (c == '\t') {
	    /* assume tabs every 8 positions */
	    db_output_position = NEXT_TAB(db_output_position);
	}
	else if (c == ' ') {
	    /* space */
	    db_output_position++;
	}
	else if (c == '\007') {
	    /* bell */
	    cnputc(c);
	    /* No need to beep in a log: db_capture_writech(c); */
	}
	/* other characters are assumed non-printing */
}