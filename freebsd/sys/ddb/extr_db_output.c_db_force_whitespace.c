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
 int NEXT_TAB (int) ; 
 int /*<<< orphan*/  cnputc (char) ; 
 int /*<<< orphan*/  db_capture_writech (char) ; 
 int db_last_non_space ; 
 int db_output_position ; 

void
db_force_whitespace(void)
{
	int last_print, next_tab;

	last_print = db_last_non_space;
	while (last_print < db_output_position) {
	    next_tab = NEXT_TAB(last_print);
	    if (next_tab <= db_output_position) {
		while (last_print < next_tab) { /* DON'T send a tab!!! */
			cnputc(' ');
			db_capture_writech(' ');
			last_print++;
		}
	    }
	    else {
		cnputc(' ');
		db_capture_writech(' ');
		last_print++;
	    }
	}
	db_last_non_space = db_output_position;
}