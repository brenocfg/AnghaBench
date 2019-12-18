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
 int NOFILE ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int /*<<< orphan*/  _SC_OPEN_MAX ; 
 int getdtablesize () ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

int
getdtsize()
{
# ifdef RLIMIT_NOFILE
	struct rlimit rl;

	if (getrlimit(RLIMIT_NOFILE, &rl) >= 0)
		return rl.rlim_cur;
# endif /* RLIMIT_NOFILE */

# if HASGETDTABLESIZE
	return getdtablesize();
# else /* HASGETDTABLESIZE */
#  ifdef _SC_OPEN_MAX
	return sysconf(_SC_OPEN_MAX);
#  else /* _SC_OPEN_MAX */
	return NOFILE;
#  endif /* _SC_OPEN_MAX */
# endif /* HASGETDTABLESIZE */
}