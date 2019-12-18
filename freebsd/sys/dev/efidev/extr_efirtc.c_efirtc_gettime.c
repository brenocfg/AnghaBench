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
struct timespec {int dummy; } ;
struct efi_tm {int /*<<< orphan*/  tm_nsec; int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct clocktime {int /*<<< orphan*/  nsec; int /*<<< orphan*/  year; int /*<<< orphan*/  mon; int /*<<< orphan*/  day; int /*<<< orphan*/  hour; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_READ ; 
 int clock_ct_to_ts (struct clocktime*,struct timespec*) ; 
 int /*<<< orphan*/  clock_dbgprint_ct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clocktime*) ; 
 int efi_get_time (struct efi_tm*) ; 

__attribute__((used)) static int
efirtc_gettime(device_t dev, struct timespec *ts)
{
	struct clocktime ct;
	struct efi_tm tm;
	int error;

	error = efi_get_time(&tm);
	if (error != 0)
		return (error);

	ct.sec = tm.tm_sec;
	ct.min = tm.tm_min;
	ct.hour = tm.tm_hour;
	ct.day = tm.tm_mday;
	ct.mon = tm.tm_mon;
	ct.year = tm.tm_year;
	ct.nsec = tm.tm_nsec;

	clock_dbgprint_ct(dev, CLOCK_DBG_READ, &ct);
	return (clock_ct_to_ts(&ct, ts));
}