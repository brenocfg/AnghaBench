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
 int /*<<< orphan*/  ocs_print_stack () ; 
 int /*<<< orphan*/  ocs_printf (char*,char const*,int,char const*) ; 

void
_ocs_hw_verify(const char *cond, const char *filename, int linenum)
{
	ocs_printf("%s(%d): HW verify (%s) failed\n", filename, linenum, cond);
	ocs_print_stack();
}