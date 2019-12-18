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
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  CRIOGET ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_handle_fd(void)
{
	int dc_fd, fd;

	dc_fd = open("/dev/crypto", O_RDWR);

	/*
	 * Why do we do this dance instead of just operating on /dev/crypto
	 * directly?  I have no idea.
	 */
	ATF_REQUIRE(dc_fd >= 0);
	ATF_REQUIRE(ioctl(dc_fd, CRIOGET, &fd) != -1);
	close(dc_fd);
	return (fd);
}