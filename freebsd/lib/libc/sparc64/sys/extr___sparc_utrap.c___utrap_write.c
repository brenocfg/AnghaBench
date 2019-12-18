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
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  __sys_write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void
__utrap_write(const char *str)
{
	int berrno;

	berrno = errno;
	__sys_write(STDERR_FILENO, str, strlen(str));
	errno = berrno;
}