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
 int /*<<< orphan*/  AFILE ; 
 int /*<<< orphan*/  ATF_CHECK_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  O_CREAT ; 
 int PARALLEL ; 
 int /*<<< orphan*/  RENDEZVOUS ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  close (int) ; 
 int done ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  handler ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  openfiles2 (size_t) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__ wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
openfiles(size_t n)
{
	int i, fd;

	signal(SIGUSR1, handler);
	ATF_REQUIRE((fd = open(AFILE, O_CREAT, 0644)) != -1);
	close(fd);
	ATF_REQUIRE((fd = open(RENDEZVOUS, O_CREAT, 0644)) != -1);
	close(fd);
	done = 0;
	for (i = 0; i < PARALLEL; i++)
		if (fork() == 0)
			openfiles2(n / PARALLEL);
	while (done != PARALLEL) {
		usleep(1000);
		ATF_REQUIRE_EQ_MSG(0, waitpid(-1, NULL, WNOHANG),
			"a child exited unexpectedly");
	}
	unlink(RENDEZVOUS);
	for (i = 0; i < PARALLEL; i++)
		ATF_CHECK_MSG(wait(NULL) > 0, "wait: %s", strerror(errno));
}