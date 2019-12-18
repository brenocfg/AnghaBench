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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct timespec {int dummy; } ;
struct clocktime {int nsec; int year; void* mon; void* day; void* hour; void* min; void* sec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int OPAL_BUSY_EVENT ; 
 int /*<<< orphan*/  OPAL_POLL_EVENTS ; 
 int /*<<< orphan*/  OPAL_RTC_READ ; 
 int OPAL_SUCCESS ; 
 void* bcd2bin (int) ; 
 int bcd2bin32 (int) ; 
 int be32toh (int) ; 
 int be64toh (int) ; 
 int clock_ct_to_ts (struct clocktime*,struct timespec*) ; 
 int opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  vtophys (int*) ; 

__attribute__((used)) static int
opal_gettime(device_t dev, struct timespec *ts)
{
	int rv;
	struct clocktime ct;
	uint32_t ymd;
	uint64_t hmsm;

	rv = opal_call(OPAL_RTC_READ, vtophys(&ymd), vtophys(&hmsm));
	while (rv == OPAL_BUSY_EVENT)  {
		opal_call(OPAL_POLL_EVENTS, 0);
		pause("opalrtc", 1);
		rv = opal_call(OPAL_RTC_READ, vtophys(&ymd), vtophys(&hmsm));
	}

	if (rv != OPAL_SUCCESS)
		return (ENXIO);

	hmsm = be64toh(hmsm);
	ymd = be32toh(ymd);

	ct.nsec	= bcd2bin32((hmsm & 0x000000ffffff0000) >> 16) * 1000;
	ct.sec	= bcd2bin((hmsm & 0x0000ff0000000000) >> 40);
	ct.min	= bcd2bin((hmsm & 0x00ff000000000000) >> 48);
	ct.hour	= bcd2bin((hmsm & 0xff00000000000000) >> 56);

	ct.day	= bcd2bin((ymd & 0x000000ff) >> 0);
	ct.mon	= bcd2bin((ymd & 0x0000ff00) >> 8);
	ct.year	= bcd2bin32((ymd & 0xffff0000) >> 16);

	return (clock_ct_to_ts(&ct, ts));
}