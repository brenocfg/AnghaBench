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
typedef  int cloudabi_timestamp_t ;

/* Variables and functions */
 int EOVERFLOW ; 
 int UINT64_MAX ; 

int
cloudabi_convert_timespec(const struct timespec *in, cloudabi_timestamp_t *out)
{
	cloudabi_timestamp_t s, ns;

	if (in->tv_sec < 0) {
		/* Timestamps from before the Epoch cannot be expressed. */
		*out = 0;
		return (EOVERFLOW);
	}
	s = in->tv_sec;
	ns = in->tv_nsec;
	if (s > UINT64_MAX / 1000000000 ||
	    (s == UINT64_MAX / 1000000000 && ns > UINT64_MAX % 1000000000)) {
		/* Addition of seconds and nanoseconds would overflow. */
		*out = UINT64_MAX;
		return (EOVERFLOW);
	}
	*out = s * 1000000000 + ns;
	return (0);
}