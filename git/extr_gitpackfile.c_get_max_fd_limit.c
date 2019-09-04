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

__attribute__((used)) static unsigned int get_max_fd_limit(void)
{
#ifdef RLIMIT_NOFILE
	{
		struct rlimit lim;

		if (!getrlimit(RLIMIT_NOFILE, &lim))
			return lim.rlim_cur;
	}
#endif

#ifdef _SC_OPEN_MAX
	{
		long open_max = sysconf(_SC_OPEN_MAX);
		if (0 < open_max)
			return open_max;
		/*
		 * Otherwise, we got -1 for one of the two
		 * reasons:
		 *
		 * (1) sysconf() did not understand _SC_OPEN_MAX
		 *     and signaled an error with -1; or
		 * (2) sysconf() said there is no limit.
		 *
		 * We _could_ clear errno before calling sysconf() to
		 * tell these two cases apart and return a huge number
		 * in the latter case to let the caller cap it to a
		 * value that is not so selfish, but letting the
		 * fallback OPEN_MAX codepath take care of these cases
		 * is a lot simpler.
		 */
	}
#endif

#ifdef OPEN_MAX
	return OPEN_MAX;
#else
	return 1; /* see the caller ;-) */
#endif
}