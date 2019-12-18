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
 int last_fd ; 
 int /*<<< orphan*/  ulog_login_pseudo (int,char const*) ; 

int
utempter_add_record(int fd, const char *host)
{

	ulog_login_pseudo(fd, host);
	last_fd = fd;
	return (0);
}