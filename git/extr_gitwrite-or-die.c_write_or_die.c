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
 int /*<<< orphan*/  check_pipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ write_in_full (int,void const*,size_t) ; 

void write_or_die(int fd, const void *buf, size_t count)
{
	if (write_in_full(fd, buf, count) < 0) {
		check_pipe(errno);
		die_errno("write error");
	}
}