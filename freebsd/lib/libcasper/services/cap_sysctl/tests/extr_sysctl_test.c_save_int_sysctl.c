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
typedef  int /*<<< orphan*/  val ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int sysctlbyname (char const*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,int*,size_t) ; 

__attribute__((used)) static void
save_int_sysctl(const char *name, const char *file)
{
	ssize_t n;
	size_t sz;
	int error, fd, val;

	sz = sizeof(val);
	error = sysctlbyname(name, &val, &sz, NULL, 0);
	ATF_REQUIRE_MSG(error == 0,
	    "sysctlbyname(%s): %s", name, strerror(errno));

	fd = open(file, O_CREAT | O_WRONLY, 0600);
	ATF_REQUIRE_MSG(fd >= 0, "open(%s): %s", file, strerror(errno));
	n = write(fd, &val, sz);
	ATF_REQUIRE(n >= 0 && (size_t)n == sz);
	error = close(fd);
	ATF_REQUIRE(error == 0);
}