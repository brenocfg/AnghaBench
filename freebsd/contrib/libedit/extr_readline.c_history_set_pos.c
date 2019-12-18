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
 int history_length ; 
 int history_offset ; 

int
history_set_pos(int pos)
{
	if (pos >= history_length || pos < 0)
		return 0;

	history_offset = pos;
	return 1;
}