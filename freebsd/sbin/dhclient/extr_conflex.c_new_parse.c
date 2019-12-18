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
 scalar_t__* cur_line ; 
 int line ; 
 scalar_t__* line1 ; 
 scalar_t__* line2 ; 
 int lpos ; 
 scalar_t__* prev_line ; 
 char const* tlname ; 
 scalar_t__* token_line ; 
 scalar_t__ warnings_occurred ; 

void
new_parse(const char *name)
{
	tlname = name;
	lpos = line = 1;
	cur_line = line1;
	prev_line = line2;
	token_line = cur_line;
	cur_line[0] = prev_line[0] = 0;
	warnings_occurred = 0;
}