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
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_year; scalar_t__ tm_isdst; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_DIV (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LDNS_MOD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_mon_and_mday_from_year_and_yday (struct tm*) ; 
 int /*<<< orphan*/  sldns_wday_from_year_and_yday (struct tm*) ; 
 int /*<<< orphan*/  sldns_year_and_yday_from_days_since_epoch (int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static struct tm *
sldns_gmtime64_r(int64_t clock, struct tm *result)
{
	result->tm_isdst = 0;
	result->tm_sec   = (int) LDNS_MOD(clock, 60);
	clock            =       LDNS_DIV(clock, 60);
	result->tm_min   = (int) LDNS_MOD(clock, 60);
	clock            =       LDNS_DIV(clock, 60);
	result->tm_hour  = (int) LDNS_MOD(clock, 24);
	clock            =       LDNS_DIV(clock, 24);

	sldns_year_and_yday_from_days_since_epoch(clock, result);
	sldns_mon_and_mday_from_year_and_yday(result);
	sldns_wday_from_year_and_yday(result);
	result->tm_year -= 1900;

	return result;
}