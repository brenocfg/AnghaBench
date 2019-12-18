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
 int /*<<< orphan*/  ATF_CHECK_EQ_MSG (int,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATF_CHECK_MSG (int,char*,char const*,...) ; 
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  errno ; 
 int getpagesize () ; 
 void* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 

__attribute__((used)) static void
checked_mmap(int prot, int flags, int fd, int error, const char *msg)
{
	void *p;
	int pagesize;

	ATF_REQUIRE((pagesize = getpagesize()) > 0);
	p = mmap(NULL, pagesize, prot, flags, fd, 0);
	if (p == MAP_FAILED) {
		if (error == 0)
			ATF_CHECK_MSG(0, "%s failed with errno %d", msg,
			    errno);
		else
			ATF_CHECK_EQ_MSG(error, errno,
			    "%s failed with wrong errno %d (expected %d)", msg,
			    errno, error);
	} else {
		ATF_CHECK_MSG(error == 0, "%s succeeded", msg);
		munmap(p, pagesize);
	}
}