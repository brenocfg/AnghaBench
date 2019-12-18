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
struct shared_info {char* tag; int message; scalar_t__ failed; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 int MAP_ANON ; 
 struct shared_info* MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  cfail (struct shared_info*,char*,char*,int) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  closefrom (int) ; 
 int /*<<< orphan*/  cok (struct shared_info*,char*) ; 
 int devnull () ; 
 scalar_t__ dup2 (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fail (char*,char*,...) ; 
 int /*<<< orphan*/  fail_err (char*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  getpagesize () ; 
 int highest_fd () ; 
 struct shared_info* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ wait (int /*<<< orphan*/ *) ; 

int
main(void)
{
	struct shared_info *info;
	pid_t pid;
	int fd, i, start;

	printf("1..15\n");

	/* We better start up with fd's 0, 1, and 2 open. */
	start = devnull();
	if (start == -1)
		fail("open", "bad descriptor %d", start);
	ok("open");

	/* Make sure highest_fd() works. */
	fd = highest_fd();
	if (start != fd)
		fail("highest_fd", "bad descriptor %d != %d", start, fd);
	ok("highest_fd");

	/* Try to use closefrom() for just closing fd 3. */
	closefrom(start + 1);
	fd = highest_fd();
	if (fd != start)
		fail("closefrom", "highest fd %d", fd);
	ok("closefrom");

	/* Eat up 16 descriptors. */
	for (i = 0; i < 16; i++)
		(void)devnull();
	fd = highest_fd();
	if (fd != start + 16)
		fail("open 16", "highest fd %d", fd);
	ok("open 16");

	/* Close half of them. */
	closefrom(11);
	fd = highest_fd();
	if (fd != 10)
		fail("closefrom", "highest fd %d", fd);
	ok("closefrom");

	/* Explicitly close descriptors 6 and 8 to create holes. */
	if (close(6) < 0 || close(8) < 0)
		fail_err("close2 ");
	ok("close 2");

	/* Verify that close on 6 and 8 fails with EBADF. */
	if (close(6) == 0)
		fail("close(6)", "did not fail");
	if (errno != EBADF)
		fail_err("close(6)");
	ok("close(6)");
	if (close(8) == 0)
		fail("close(8)", "did not fail");
	if (errno != EBADF)
		fail_err("close(8)");
	ok("close(8)");

	/* Close from 4 on. */
	closefrom(4);
	fd = highest_fd();
	if (fd != 3)
		fail("closefrom", "highest fd %d", fd);
	ok("closefrom");

	/* Allocate a small SHM region for IPC with our child. */
	info = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON |
	    MAP_SHARED, -1, 0);
	if (info == MAP_FAILED)
		fail_err("mmap");
	ok("mmap");

	/* Fork a child process to test closefrom(0). */
	pid = fork();
	if (pid < 0)
		fail_err("fork");
	if (pid == 0) {
		/* Child. */
		closefrom(0);
		fd = highest_fd();
		if (fd >= 0)
			cfail(info, "closefrom(0)", "highest fd %d", fd);
		cok(info, "closefrom(0)");
	}
	if (wait(NULL) < 0)
		fail_err("wait");
	if (info->failed)
		fail(info->tag, "%s", info->message);
	ok(info->tag);

	/* Fork a child process to test closefrom(-1). */
	pid = fork();
	if (pid < 0)
		fail_err("fork");
	if (pid == 0) {
		/* Child. */
		closefrom(-1);
		fd = highest_fd();
		if (fd >= 0)
			cfail(info, "closefrom(-1)", "highest fd %d", fd);
		cok(info, "closefrom(-1)");
	}
	if (wait(NULL) < 0)
		fail_err("wait");
	if (info->failed)
		fail(info->tag, "%s", info->message);
	ok(info->tag);

	/* Dup stdout to 6. */
	if (dup2(1, 6) < 0)
		fail_err("dup2");
	fd = highest_fd();
	if (fd != 6)
		fail("dup2", "highest fd %d", fd);
	ok("dup2");

	/* Do a closefrom() starting in a hole. */
	closefrom(4);
	fd = highest_fd();
	if (fd != 3)
		fail("closefrom", "highest fd %d", fd);
	ok("closefrom");

	/* Do a closefrom() beyond our highest open fd. */
	closefrom(32);
	fd = highest_fd();
	if (fd != 3)
		fail("closefrom", "highest fd %d", fd);
	ok("closefrom");

	return (0);
}