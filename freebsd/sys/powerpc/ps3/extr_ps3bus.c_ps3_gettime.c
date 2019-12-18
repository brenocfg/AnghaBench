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
typedef  scalar_t__ uint64_t ;
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ Y2K ; 
 int lv1_get_rtc (scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
ps3_gettime(device_t dev, struct timespec *ts)
{
	uint64_t rtc, tb;
	int result;

	result = lv1_get_rtc(&rtc, &tb);
	if (result)
		return (result);

	ts->tv_sec = rtc + Y2K;
	ts->tv_nsec = 0;
	return (0);
}