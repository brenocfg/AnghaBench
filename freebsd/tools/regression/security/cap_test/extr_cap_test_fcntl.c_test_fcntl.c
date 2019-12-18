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
struct fd {char* member_0; int member_1; int f_fd; int /*<<< orphan*/  f_name; } ;
typedef  int cap_rights_t ;
typedef  int /*<<< orphan*/  all ;

/* Variables and functions */
 int CAP_FCNTL ; 
 int CAP_READ ; 
 int /*<<< orphan*/  CHECK_NOTCAPABLE (int (*) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_SYSCALL_SUCCEEDS (int (*) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAIL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PASSED ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  SHM_ANON ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int cap_enter () ; 
 int cap_new (int,int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int shm_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
test_fcntl(void)
{
	int success = PASSED;
	cap_rights_t rights = CAP_READ | CAP_FCNTL;

	/*
	 * Open some files of different types, and wrap them in capabilities.
	 */
	struct fd files[] = {
		{ "file",         open("/etc/passwd", O_RDONLY) },
		{ "socket",       socket(PF_LOCAL, SOCK_STREAM, 0) },
		{ "SHM",          shm_open(SHM_ANON, O_RDWR, 0600) },
	};
	REQUIRE(files[0].f_fd);
	REQUIRE(files[1].f_fd);
	REQUIRE(files[2].f_fd);

	struct fd caps[] = {
		{ "file cap",     cap_new(files[0].f_fd, rights) },
		{ "socket cap",   cap_new(files[1].f_fd, rights) },
		{ "SHM cap",      cap_new(files[2].f_fd, rights) },
	};
	REQUIRE(caps[0].f_fd);
	REQUIRE(caps[1].f_fd);
	REQUIRE(caps[2].f_fd);

	struct fd all[] = {
		files[0], caps[0],
		files[1], caps[1],
		files[2], caps[2],
	};
	const size_t len = sizeof(all) / sizeof(struct fd);

	REQUIRE(cap_enter());

	/*
	 * Ensure that we can fcntl() all the files that we opened above.
	 */
	for (size_t i = 0; i < len; i++)
	{
		struct fd f = all[i];
		int cap;

		CHECK_SYSCALL_SUCCEEDS(fcntl, f.f_fd, F_GETFL, 0);
		REQUIRE(cap = cap_new(f.f_fd, CAP_READ));
		if (fcntl(f.f_fd, F_GETFL, 0) == -1)
			FAIL("Error calling fcntl('%s', F_GETFL)", f.f_name);
		else
			CHECK_NOTCAPABLE(fcntl, cap, F_GETFL, 0);
	}

	return (success);
}