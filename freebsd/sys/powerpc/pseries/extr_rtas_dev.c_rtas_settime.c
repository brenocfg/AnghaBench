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
struct clocktime {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  mon; int /*<<< orphan*/  year; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int cell_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENXIO ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec*,struct clocktime*) ; 
 int rtas_call_method (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int rtas_token_lookup (char*) ; 

__attribute__((used)) static int
rtas_settime(device_t dev, struct timespec *ts)
{
	struct clocktime ct;
	cell_t token, status;
	int error;
	
	token = rtas_token_lookup("set-time-of-day");
	if (token == -1)
		return (ENXIO);

	clock_ts_to_ct(ts, &ct);
	error = rtas_call_method(token, 7, 1, ct.year, ct.mon, ct.day, ct.hour,
	    ct.min, ct.sec, ct.nsec, &status);
	if (error < 0)
		return (ENXIO);
	if (status != 0)
		return (((int)status < 0) ? ENXIO : EAGAIN);

	return (0);
}