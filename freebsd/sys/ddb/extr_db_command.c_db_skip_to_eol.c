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
 int db_read_token () ; 
 int tEOL ; 

void
db_skip_to_eol(void)
{
	int	t;
	do {
	    t = db_read_token();
	} while (t != tEOL);
}