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
typedef  void* time_t ;
struct tm {int dummy; } ;
typedef  void* int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 struct tm* gmtime_r (void**,struct tm*) ; 
 struct tm* ldns_gmtime64_r (void*,struct tm*) ; 
 void* ldns_serial_arithmitics_time (int /*<<< orphan*/ ,void*) ; 

struct tm *
ldns_serial_arithmitics_gmtime_r(int32_t time, time_t now, struct tm *result)
{
#if SIZEOF_TIME_T <= 4
	int64_t secs_since_epoch = ldns_serial_arithmitics_time(time, now);
	return  ldns_gmtime64_r(secs_since_epoch, result);
#else
	time_t  secs_since_epoch = ldns_serial_arithmitics_time(time, now);
	return  gmtime_r(&secs_since_epoch, result);
#endif
}