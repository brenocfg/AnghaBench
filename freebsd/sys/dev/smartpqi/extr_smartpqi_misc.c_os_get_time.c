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
typedef  void* uint8_t ;
struct timespec {int dummy; } ;
struct clocktime {int hour; int min; int sec; int mon; int day; int year; } ;
struct bmic_host_wellness_time {void* year; void* century; void* day; void* month; scalar_t__ reserved; void* sec; void* min; void* hour; } ;

/* Variables and functions */
 scalar_t__ bin2bcd (int) ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec*,struct clocktime*) ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 

void os_get_time(struct bmic_host_wellness_time *host_wellness_time)
{
	struct timespec ts;
	struct clocktime ct;

	getnanotime(&ts);
	clock_ts_to_ct(&ts, &ct);


	/* Fill the time In BCD Format */
	host_wellness_time->hour= (uint8_t)bin2bcd(ct.hour);
	host_wellness_time->min = (uint8_t)bin2bcd(ct.min);
	host_wellness_time->sec= (uint8_t)bin2bcd(ct.sec);
	host_wellness_time->reserved = 0;
	host_wellness_time->month = (uint8_t)bin2bcd(ct.mon);
	host_wellness_time->day = (uint8_t)bin2bcd(ct.day);
	host_wellness_time->century = (uint8_t)bin2bcd(ct.year / 100);
	host_wellness_time->year = (uint8_t)bin2bcd(ct.year % 100);

}