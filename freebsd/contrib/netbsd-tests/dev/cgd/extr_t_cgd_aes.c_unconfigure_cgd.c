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
struct cgd_ioctl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGDIOCCLR ; 
 int rump_sys_ioctl (int,int /*<<< orphan*/ ,struct cgd_ioctl*) ; 

__attribute__((used)) static int
unconfigure_cgd(int fd)
{
	struct cgd_ioctl ci;

	return rump_sys_ioctl(fd, CGDIOCCLR, &ci);
}