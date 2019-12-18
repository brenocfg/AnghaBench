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
struct rlimit {int rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  setdtablesize (int) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

__attribute__((used)) static int
fdlim_set(int lim)
{
#if defined(HAVE_SETRLIMIT) && defined(RLIMIT_NOFILE)
	struct rlimit rlfd;
#endif

	if (lim <= 0)
		return (-1);
#if defined(HAVE_SETRLIMIT) && defined(RLIMIT_NOFILE)
	if (getrlimit(RLIMIT_NOFILE, &rlfd) < 0)
		return (-1);
	rlfd.rlim_cur = lim;
	if (setrlimit(RLIMIT_NOFILE, &rlfd) < 0)
		return (-1);
#elif defined (HAVE_SETDTABLESIZE)
	setdtablesize(lim);
#endif
	return (0);
}