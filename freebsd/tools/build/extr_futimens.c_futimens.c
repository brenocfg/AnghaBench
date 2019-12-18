#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_3__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct stat {TYPE_2__ st_mtim; TYPE_1__ st_atim; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int UTIME_NOW ; 
 int UTIME_OMIT ; 
 int /*<<< orphan*/  errno ; 
 int fstat (int,struct stat*) ; 
 int futimes (int,struct timeval*) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

int
futimens(int fd, const struct timespec times[2])
{
	struct timeval now, tv[2], *tvp;
	struct stat sb;
	int osreldate;

	if (times == NULL || (times[0].tv_nsec == UTIME_NOW &&
	    times[1].tv_nsec == UTIME_NOW))
		tvp = NULL;
	else if (times[0].tv_nsec == UTIME_OMIT &&
	    times[1].tv_nsec == UTIME_OMIT)
		return (0);
	else {
		if ((times[0].tv_nsec < 0 || times[0].tv_nsec > 999999999) &&
		    times[0].tv_nsec != UTIME_NOW &&
		    times[0].tv_nsec != UTIME_OMIT) {
			errno = EINVAL;
			return (-1);
		}
		if ((times[1].tv_nsec < 0 || times[1].tv_nsec > 999999999) &&
		    times[1].tv_nsec != UTIME_NOW &&
		    times[1].tv_nsec != UTIME_OMIT) {
			errno = EINVAL;
			return (-1);
		}
		tv[0].tv_sec = times[0].tv_sec;
		tv[0].tv_usec = times[0].tv_nsec / 1000;
		tv[1].tv_sec = times[1].tv_sec;
		tv[1].tv_usec = times[1].tv_nsec / 1000;
		tvp = tv;
		if (times[0].tv_nsec == UTIME_OMIT ||
		    times[1].tv_nsec == UTIME_OMIT) {
			if (fstat(fd, &sb) == -1)
				return (-1);
			if (times[0].tv_nsec == UTIME_OMIT) {
				tv[0].tv_sec = sb.st_atim.tv_sec;
				tv[0].tv_usec = sb.st_atim.tv_nsec / 1000;
			}
			if (times[1].tv_nsec == UTIME_OMIT) {
				tv[1].tv_sec = sb.st_mtim.tv_sec;
				tv[1].tv_usec = sb.st_mtim.tv_nsec / 1000;
			}
		}
		if (times[0].tv_nsec == UTIME_NOW ||
		    times[1].tv_nsec == UTIME_NOW) {
			if (gettimeofday(&now, NULL) == -1)
				return (-1);
			if (times[0].tv_nsec == UTIME_NOW)
				tv[0] = now;
			if (times[1].tv_nsec == UTIME_NOW)
				tv[1] = now;
		}
	}
	return (futimes(fd, tvp));
}