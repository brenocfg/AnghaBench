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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  atf_tc_fail (char*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int getpagesize () ; 
 scalar_t__ isprint (char) ; 
 char* mmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (char*,int) ; 
 int shm_open (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
verify_object(const char *path, char expected_value)
{
	int fd;
	int pagesize;
	char *page;

	ATF_REQUIRE(0 < (pagesize = getpagesize()));

	fd = shm_open(path, O_RDONLY, 0777);
	if (fd < 0)
		atf_tc_fail("shm_open failed in verify_object; errno=%d, path=%s",
		    errno, path);

	page = mmap(0, pagesize, PROT_READ, MAP_SHARED, fd, 0);
	if (page == MAP_FAILED)
		atf_tc_fail("mmap(1)");
	if (page[0] != expected_value)
		atf_tc_fail("Renamed object has incorrect value; has"
		    "%d (0x%x, '%c'), expected %d (0x%x, '%c')\n",
		    page[0], page[0], isprint(page[0]) ? page[0] : ' ',
		    expected_value, expected_value,
		    isprint(expected_value) ? expected_value : ' ');
	ATF_REQUIRE_MSG(munmap(page, pagesize) == 0, "munmap failed; errno=%d",
	    errno);
	close(fd);
}