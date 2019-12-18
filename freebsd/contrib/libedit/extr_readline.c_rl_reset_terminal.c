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
 int /*<<< orphan*/  el_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h ; 
 int /*<<< orphan*/  rl_initialize () ; 

int
rl_reset_terminal(const char *p __attribute__((__unused__)))
{

	if (h == NULL || e == NULL)
		rl_initialize();
	el_reset(e);
	return 0;
}