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
typedef  int uint8_t ;
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_READ ; 
 int /*<<< orphan*/  DS1672_COUNTER ; 
 int /*<<< orphan*/  clock_dbgprint_ts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*) ; 
 int ds1672_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
ds1672_gettime(device_t dev, struct timespec *ts)
{
	uint8_t secs[4];
	int error;

	error = ds1672_read(dev, DS1672_COUNTER, secs, 4);
	if (error == 0) {
		/* counter has seconds since epoch */
		ts->tv_sec = (secs[3] << 24) | (secs[2] << 16)
			   | (secs[1] <<  8) | (secs[0] <<  0);
		ts->tv_nsec = 0;
	}
	clock_dbgprint_ts(dev, CLOCK_DBG_READ, ts); 
	return (error);
}