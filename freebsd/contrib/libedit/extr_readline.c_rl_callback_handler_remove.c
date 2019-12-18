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
 int /*<<< orphan*/  el_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rl_linefunc ; 

void
rl_callback_handler_remove(void)
{
	rl_linefunc = NULL;
	el_end(e);
	e = NULL;
}