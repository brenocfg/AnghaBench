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
 int ERR ; 
 int OK ; 
 int /*<<< orphan*/  report_status (char*) ; 
 int /*<<< orphan*/  report_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ret_err ; 
 int /*<<< orphan*/  ret_ok ; 

void
report_return(int status)
{
	if (status == ERR)
		report_type(ret_err);
	else if (status == OK)
		report_type(ret_ok);
	else
		report_status("INVALID_RETURN");
}