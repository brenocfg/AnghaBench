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
struct timespec {long tv_nsec; void* tv_sec; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int EINVAL ; 
 int UIO_SYSSPACE ; 
 int UTIMENS_EXIT ; 
 int UTIMENS_NULL ; 
 long UTIME_NOW ; 
 long UTIME_OMIT ; 
 void* VNOVAL ; 
 int copyin (struct timespec const*,struct timespec*,int) ; 
 int /*<<< orphan*/  vfs_timestamp (struct timespec*) ; 

__attribute__((used)) static int
getutimens(const struct timespec *usrtsp, enum uio_seg tspseg,
    struct timespec *tsp, int *retflags)
{
	struct timespec tsnow;
	int error;

	vfs_timestamp(&tsnow);
	*retflags = 0;
	if (usrtsp == NULL) {
		tsp[0] = tsnow;
		tsp[1] = tsnow;
		*retflags |= UTIMENS_NULL;
		return (0);
	}
	if (tspseg == UIO_SYSSPACE) {
		tsp[0] = usrtsp[0];
		tsp[1] = usrtsp[1];
	} else if ((error = copyin(usrtsp, tsp, sizeof(*tsp) * 2)) != 0)
		return (error);
	if (tsp[0].tv_nsec == UTIME_OMIT && tsp[1].tv_nsec == UTIME_OMIT)
		*retflags |= UTIMENS_EXIT;
	if (tsp[0].tv_nsec == UTIME_NOW && tsp[1].tv_nsec == UTIME_NOW)
		*retflags |= UTIMENS_NULL;
	if (tsp[0].tv_nsec == UTIME_OMIT)
		tsp[0].tv_sec = VNOVAL;
	else if (tsp[0].tv_nsec == UTIME_NOW)
		tsp[0] = tsnow;
	else if (tsp[0].tv_nsec < 0 || tsp[0].tv_nsec >= 1000000000L)
		return (EINVAL);
	if (tsp[1].tv_nsec == UTIME_OMIT)
		tsp[1].tv_sec = VNOVAL;
	else if (tsp[1].tv_nsec == UTIME_NOW)
		tsp[1] = tsnow;
	else if (tsp[1].tv_nsec < 0 || tsp[1].tv_nsec >= 1000000000L)
		return (EINVAL);

	return (0);
}