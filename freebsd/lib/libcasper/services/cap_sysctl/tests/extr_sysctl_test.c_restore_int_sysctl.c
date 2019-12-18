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
 int /*<<< orphan*/  O_RDONLY ; 
 int close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,int*,size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int sysctlbyname (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,size_t) ; 
 int unlink (char const*) ; 

__attribute__((used)) static void
restore_int_sysctl(const char *name, const char *file)
{
	ssize_t n;
	size_t sz;
	int error, fd, val;

	fd = open(file, O_RDONLY);
	ATF_REQUIRE(fd >= 0);
	sz = sizeof(val);
	n = read(fd, &val, sz);
	ATF_REQUIRE(n >= 0 && (size_t)n == sz);
	error = unlink(file);
	ATF_REQUIRE(error == 0);
	error = close(fd);
	ATF_REQUIRE(error == 0);

	error = sysctlbyname(name, NULL, NULL, &val, sz);
	ATF_REQUIRE_MSG(error == 0,
	    "sysctlbyname(%s): %s", name, strerror(errno));
}