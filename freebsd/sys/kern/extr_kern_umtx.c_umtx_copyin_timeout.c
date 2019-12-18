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
struct timespec {scalar_t__ tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int EINVAL ; 
 int copyin (void const*,struct timespec*,int) ; 

inline int
umtx_copyin_timeout(const void *addr, struct timespec *tsp)
{
	int error;

	error = copyin(addr, tsp, sizeof(struct timespec));
	if (error == 0) {
		if (tsp->tv_sec < 0 ||
		    tsp->tv_nsec >= 1000000000 ||
		    tsp->tv_nsec < 0)
			error = EINVAL;
	}
	return (error);
}