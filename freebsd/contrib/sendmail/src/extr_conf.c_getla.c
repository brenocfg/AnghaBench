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
 int /*<<< orphan*/  sm_dprintf (char*) ; 
 scalar_t__ tTd (int,int) ; 

int
getla()
{
	if (tTd(3, 1))
		sm_dprintf("getla: ZERO\n");
	return 0;
}