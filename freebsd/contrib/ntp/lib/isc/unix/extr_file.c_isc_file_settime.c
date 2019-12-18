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
struct timeval {long tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  isc_time_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  scalar_t__ isc_int32_t ;

/* Variables and functions */
 int CHAR_BIT ; 
 int /*<<< orphan*/  ISC_R_RANGE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  isc__errno2result (int /*<<< orphan*/ ) ; 
 int isc_time_nanoseconds (int /*<<< orphan*/ *) ; 
 scalar_t__ isc_time_seconds (int /*<<< orphan*/ *) ; 
 scalar_t__ utimes (char const*,struct timeval*) ; 

isc_result_t
isc_file_settime(const char *file, isc_time_t *itime) {
	struct timeval times[2];

	REQUIRE(file != NULL && itime != NULL);

	/*
	 * tv_sec is at least a 32 bit quantity on all platforms we're
	 * dealing with, but it is signed on most (all?) of them,
	 * so we need to make sure the high bit isn't set.  This unfortunately
	 * loses when either:
	 *   * tv_sec becomes a signed 64 bit integer but long is 32 bits
	 *	and isc_time_seconds > LONG_MAX, or
	 *   * isc_time_seconds is changed to be > 32 bits but long is 32 bits
	 *      and isc_time_seconds has at least 33 significant bits.
	 */
	times[0].tv_sec = times[1].tv_sec = (long)isc_time_seconds(itime);

	/*
	 * Here is the real check for the high bit being set.
	 */
	if ((times[0].tv_sec &
	     (1ULL << (sizeof(times[0].tv_sec) * CHAR_BIT - 1))) != 0)
		return (ISC_R_RANGE);

	/*
	 * isc_time_nanoseconds guarantees a value that divided by 1000 will
	 * fit into the minimum possible size tv_usec field.  Unfortunately,
	 * we don't know what that type is so can't cast directly ... but
	 * we can at least cast to signed so the IRIX compiler shuts up.
	 */
	times[0].tv_usec = times[1].tv_usec =
		(isc_int32_t)(isc_time_nanoseconds(itime) / 1000);

	if (utimes(file, times) < 0)
		return (isc__errno2result(errno));

	return (ISC_R_SUCCESS);
}