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
struct lock_file {int dummy; } ;

/* Variables and functions */
 int BACKOFF_MAX_MULTIPLIER ; 
 scalar_t__ EEXIST ; 
 int INITIAL_BACKOFF_MS ; 
 scalar_t__ errno ; 
 scalar_t__ getpid () ; 
 int lock_file (struct lock_file*,char const*,int) ; 
 int rand () ; 
 int /*<<< orphan*/  sleep_millisec (long) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 

__attribute__((used)) static int lock_file_timeout(struct lock_file *lk, const char *path,
			     int flags, long timeout_ms)
{
	int n = 1;
	int multiplier = 1;
	long remaining_ms = 0;
	static int random_initialized = 0;

	if (timeout_ms == 0)
		return lock_file(lk, path, flags);

	if (!random_initialized) {
		srand((unsigned int)getpid());
		random_initialized = 1;
	}

	if (timeout_ms > 0)
		remaining_ms = timeout_ms;

	while (1) {
		long backoff_ms, wait_ms;
		int fd;

		fd = lock_file(lk, path, flags);

		if (fd >= 0)
			return fd; /* success */
		else if (errno != EEXIST)
			return -1; /* failure other than lock held */
		else if (timeout_ms > 0 && remaining_ms <= 0)
			return -1; /* failure due to timeout */

		backoff_ms = multiplier * INITIAL_BACKOFF_MS;
		/* back off for between 0.75*backoff_ms and 1.25*backoff_ms */
		wait_ms = (750 + rand() % 500) * backoff_ms / 1000;
		sleep_millisec(wait_ms);
		remaining_ms -= wait_ms;

		/* Recursion: (n+1)^2 = n^2 + 2n + 1 */
		multiplier += 2*n + 1;
		if (multiplier > BACKOFF_MAX_MULTIPLIER)
			multiplier = BACKOFF_MAX_MULTIPLIER;
		else
			n++;
	}
}