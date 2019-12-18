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
struct rlimit {int rlim_cur; int rlim_max; } ;

/* Variables and functions */
 int FD_SETSIZE ; 
 int /*<<< orphan*/  RLIMIT_CPU ; 
 int /*<<< orphan*/  RLIMIT_FSIZE ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int RLIM_INFINITY ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  ulimit (int,int) ; 

void
resetlimits()
{
#if HASSETRLIMIT
	struct rlimit lim;

	lim.rlim_cur = lim.rlim_max = RLIM_INFINITY;
	(void) setrlimit(RLIMIT_CPU, &lim);
	(void) setrlimit(RLIMIT_FSIZE, &lim);
# ifdef RLIMIT_NOFILE
	lim.rlim_cur = lim.rlim_max = FD_SETSIZE;
	(void) setrlimit(RLIMIT_NOFILE, &lim);
# endif /* RLIMIT_NOFILE */
#else /* HASSETRLIMIT */
# if HASULIMIT
	(void) ulimit(2, 0x3fffff);
	(void) ulimit(4, FD_SETSIZE);
# endif /* HASULIMIT */
#endif /* HASSETRLIMIT */
	errno = 0;
}