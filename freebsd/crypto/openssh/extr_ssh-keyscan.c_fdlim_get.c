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
struct rlimit {scalar_t__ rlim_max; scalar_t__ rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 scalar_t__ RLIM_INFINITY ; 
 int SSH_SYSFDMAX ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

__attribute__((used)) static int
fdlim_get(int hard)
{
#if defined(HAVE_GETRLIMIT) && defined(RLIMIT_NOFILE)
	struct rlimit rlfd;

	if (getrlimit(RLIMIT_NOFILE, &rlfd) < 0)
		return (-1);
	if ((hard ? rlfd.rlim_max : rlfd.rlim_cur) == RLIM_INFINITY)
		return SSH_SYSFDMAX;
	else
		return hard ? rlfd.rlim_max : rlfd.rlim_cur;
#else
	return SSH_SYSFDMAX;
#endif
}