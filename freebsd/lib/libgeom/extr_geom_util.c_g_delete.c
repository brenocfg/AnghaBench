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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGDELETE ; 
 int g_ioctl_arg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
g_delete(int fd, off_t offset, off_t length)
{
	off_t arg[2];

	arg[0] = offset;
	arg[1] = length;
	return (g_ioctl_arg(fd, DIOCGDELETE, arg));
}