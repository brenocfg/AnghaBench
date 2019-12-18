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
struct timespec {scalar_t__ tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct pollfd {int revents; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int POLLIN ; 
 int /*<<< orphan*/  atf_tc_fail (char*,...) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  get_records (char const*,int /*<<< orphan*/ *) ; 
 int ppoll (struct pollfd*,int,struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_auditpipe(struct pollfd fd[], const char *auditregex, FILE *pipestream)
{
	struct timespec currtime, endtime, timeout;

	/* Set the expire time for poll(2) while waiting for syscall audit */
	ATF_REQUIRE_EQ(0, clock_gettime(CLOCK_MONOTONIC, &endtime));
	endtime.tv_sec += 10;
	timeout.tv_nsec = endtime.tv_nsec;

	for (;;) {
		/* Update the time left for auditpipe to return any event */
		ATF_REQUIRE_EQ(0, clock_gettime(CLOCK_MONOTONIC, &currtime));
		timeout.tv_sec = endtime.tv_sec - currtime.tv_sec;

		switch (ppoll(fd, 1, &timeout, NULL)) {
		/* ppoll(2) returns, check if it's what we want */
		case 1:
			if (fd[0].revents & POLLIN) {
				if (get_records(auditregex, pipestream))
					return;
			} else {
				atf_tc_fail("Auditpipe returned an "
				"unknown event %#x", fd[0].revents);
			}
			break;

		/* poll(2) timed out */
		case 0:
			atf_tc_fail("%s not found in auditpipe within the "
					"time limit", auditregex);
			break;

		/* poll(2) standard error */
		case -1:
			atf_tc_fail("Poll: %s", strerror(errno));
			break;

		default:
			atf_tc_fail("Poll returned too many file descriptors");
		}
	}
}