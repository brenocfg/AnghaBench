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
 scalar_t__ buffer_fdinit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  die_errno (char*,int) ; 
 scalar_t__ first_commit_done ; 
 int /*<<< orphan*/  report_buffer ; 

void fast_export_init(int fd)
{
	first_commit_done = 0;
	if (buffer_fdinit(&report_buffer, fd))
		die_errno("cannot read from file descriptor %d", fd);
}