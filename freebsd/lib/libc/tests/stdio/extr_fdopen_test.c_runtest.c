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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char const*,int,char const*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char const*) ; 
 int open (char const*,int) ; 

__attribute__((used)) static void
runtest(const char *fname, int intmode, const char *strmode, bool success)
{
	FILE *fp;
	int fd;

	fd = open(fname, intmode);
	ATF_REQUIRE_MSG(fd != -1,
	    "open(\"%s\", %#x) failed; errno=%d", fname, intmode, errno);

	fp = fdopen(fd, strmode);
	if (fp == NULL) {
		close(fd);
		ATF_REQUIRE_MSG(success == false,
		    "fdopen(open(\"%s\", %#x), \"%s\") succeeded unexpectedly",
		    fname, intmode, strmode);
		return;
	}
	ATF_REQUIRE_MSG(success == true,
	    "fdopen(open(\"%s\", %#x), \"%s\") failed; errno=%d",
	    fname, intmode, strmode, errno);
	fclose(fp);
}