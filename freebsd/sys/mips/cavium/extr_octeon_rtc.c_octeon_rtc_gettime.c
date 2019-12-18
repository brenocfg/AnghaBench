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
typedef  scalar_t__ uint32_t ;
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOTSUP ; 
 scalar_t__ cvmx_rtc_read () ; 

__attribute__((used)) static int
octeon_rtc_gettime(device_t dev, struct timespec *ts)
{
	uint32_t secs;

	secs = cvmx_rtc_read();
	if (secs == 0)
		return (ENOTSUP);

	ts->tv_sec = secs;
	ts->tv_nsec = 0;

	return (0);
}