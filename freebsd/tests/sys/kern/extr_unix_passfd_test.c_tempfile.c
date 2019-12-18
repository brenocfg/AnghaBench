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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char*) ; 
 int PATH_MAX ; 
 char* getenv (char*) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
tempfile(int *fdp)
{
	char path[PATH_MAX];
	int fd;

	snprintf(path, PATH_MAX, "%s/unix_passfd.XXXXXXXXXXXXXXX",
	    getenv("TMPDIR") == NULL ? "/tmp" : getenv("TMPDIR"));
	fd = mkstemp(path);
	ATF_REQUIRE_MSG(fd != -1, "mkstemp(%s) failed", path);
	(void)unlink(path);
	*fdp = fd;
}