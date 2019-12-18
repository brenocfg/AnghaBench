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
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  notok_mode (char const*,char*,int) ; 
 int /*<<< orphan*/  ok_mode (char const*,int /*<<< orphan*/ *,int) ; 
 int open (char const*,int) ; 

__attribute__((used)) static void
try_directory_open(const char *testname, const char *directory,
    int mode, int expected_errno)
{
	int dfd;

	dfd = open(directory, mode);
	if (dfd >= 0) {
		if (expected_errno)
			notok_mode(testname, "opened", mode);
		else
			ok_mode(testname, NULL, mode);
		close(dfd);
	} else {
		if (expected_errno && expected_errno == errno)
			ok_mode(testname, NULL, mode);
		else if (expected_errno != 0)
			notok_mode(testname, "wrong errno", mode);
		else
			notok_mode(testname, "failed", mode);
	}
}