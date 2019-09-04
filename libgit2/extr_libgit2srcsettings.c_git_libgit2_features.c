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

int git_libgit2_features(void)
{
	return 0
#ifdef GIT_THREADS
		| GIT_FEATURE_THREADS
#endif
#ifdef GIT_HTTPS
		| GIT_FEATURE_HTTPS
#endif
#if defined(GIT_SSH)
		| GIT_FEATURE_SSH
#endif
#if defined(GIT_USE_NSEC)
		| GIT_FEATURE_NSEC
#endif
	;
}