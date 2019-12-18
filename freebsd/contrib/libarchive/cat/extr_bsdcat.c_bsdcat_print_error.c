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
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  archive_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsdcat_current_path ; 
 int exit_status ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bsdcat_print_error(void)
{
	lafe_warnc(0, "%s: %s",
	    bsdcat_current_path, archive_error_string(a));
	exit_status = 1;
}