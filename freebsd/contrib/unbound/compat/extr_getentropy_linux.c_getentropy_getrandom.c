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
 int EINTR ; 
 int /*<<< orphan*/  SYS_getrandom ; 
 int errno ; 
 int syscall (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getentropy_getrandom(void *buf, size_t len)
{
	int pre_errno = errno;
	int ret;
	if (len > 256)
		return (-1);
	do {
		ret = syscall(SYS_getrandom, buf, len, 0);
	} while (ret == -1 && errno == EINTR);

	if (ret != (int)len)
		return (-1);
	errno = pre_errno;
	return (0);
}