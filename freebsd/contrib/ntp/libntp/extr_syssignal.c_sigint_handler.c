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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_ARG (int) ; 
 int /*<<< orphan*/  ctrl_c_hook () ; 
 int /*<<< orphan*/  stub1 () ; 

RETSIGTYPE
sigint_handler(
	int	signum
	)
{
	UNUSED_ARG(signum);
	if (ctrl_c_hook != NULL)
		(*ctrl_c_hook)();
}