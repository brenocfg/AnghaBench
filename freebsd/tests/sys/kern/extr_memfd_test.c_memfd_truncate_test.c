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
 int /*<<< orphan*/  F_ADD_SEALS ; 
 int /*<<< orphan*/  MFD_ALLOW_SEALING ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int) ; 
 int ftruncate (int,int) ; 
 int memfd_create (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
memfd_truncate_test(int initial_size, int dest_size, int seals)
{
	int err, fd;

	ATF_REQUIRE((fd = memfd_create("...", MFD_ALLOW_SEALING)) != -1);
	ATF_REQUIRE(ftruncate(fd, initial_size) == 0);

	ATF_REQUIRE(fcntl(fd, F_ADD_SEALS, seals) == 0);

	err = ftruncate(fd, dest_size);
	if (err != 0)
		err = errno;
	close(fd);
	return (err);
}