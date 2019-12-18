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
 int /*<<< orphan*/ * e ; 
 int /*<<< orphan*/ * h ; 
 int /*<<< orphan*/  history_length ; 
 int /*<<< orphan*/  history_offset ; 
 int /*<<< orphan*/  rl_initialize () ; 

void
using_history(void)
{
	if (h == NULL || e == NULL)
		rl_initialize();
	history_offset = history_length;
}