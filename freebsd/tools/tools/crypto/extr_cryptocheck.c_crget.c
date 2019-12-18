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
 int /*<<< orphan*/  CRIOGET ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  devcrypto () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
crget(void)
{
	int fd;

	if (ioctl(devcrypto(), CRIOGET, &fd) == -1)
		err(1, "ioctl(CRIOGET)");
	if (fcntl(fd, F_SETFD, 1) == -1)
		err(1, "fcntl(F_SETFD) (crget)");
	return fd;
}