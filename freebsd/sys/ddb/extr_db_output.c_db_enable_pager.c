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
 scalar_t__ db_lines_per_page ; 
 scalar_t__ db_maxlines ; 
 scalar_t__ db_newlines ; 
 scalar_t__ db_pager_quit ; 

void
db_enable_pager(void)
{
	if (db_maxlines == 0) {
		db_maxlines = db_lines_per_page;
		db_newlines = 0;
		db_pager_quit = 0;
	}
}