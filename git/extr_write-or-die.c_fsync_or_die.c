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
 int /*<<< orphan*/  die_errno (char*,char const*) ; 
 scalar_t__ fsync (int) ; 

void fsync_or_die(int fd, const char *msg)
{
	if (fsync(fd) < 0) {
		die_errno("fsync error on '%s'", msg);
	}
}