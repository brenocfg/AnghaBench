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
 scalar_t__ db_max_width ; 
 scalar_t__ db_output_position ; 
 int /*<<< orphan*/  db_printf (char*) ; 

void
db_end_line(int field_width)
{
	if (db_output_position + field_width > db_max_width)
	    db_printf("\n");
}