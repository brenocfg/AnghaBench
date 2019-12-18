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
 int veriexec_check_fd_mode (int,int /*<<< orphan*/ ) ; 

int
veriexec_check_fd(int fd)
{
	return veriexec_check_fd_mode(fd, 0);
}