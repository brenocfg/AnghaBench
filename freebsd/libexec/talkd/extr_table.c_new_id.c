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
 int MAX_ID ; 

int
new_id(void)
{
	static int current_id = 0;

	current_id = (current_id + 1) % MAX_ID;
	/* 0 is reserved, helps to pick up bugs */
	if (current_id == 0)
		current_id = 1;
	return (current_id);
}