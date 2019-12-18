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
typedef  scalar_t__ timestamp_t ;
struct ident_split {scalar_t__ tz_begin; scalar_t__ tz_end; scalar_t__ date_begin; scalar_t__ date_end; } ;
struct date_mode {int dummy; } ;

/* Variables and functions */
 long INT_MAX ; 
 long INT_MIN ; 
 scalar_t__ date_overflows (scalar_t__) ; 
 scalar_t__ parse_timestamp (scalar_t__,int /*<<< orphan*/ *,int) ; 
 char const* show_date (scalar_t__,long,struct date_mode const*) ; 
 long strtol (scalar_t__,int /*<<< orphan*/ *,int) ; 

const char *show_ident_date(const struct ident_split *ident,
			    const struct date_mode *mode)
{
	timestamp_t date = 0;
	long tz = 0;

	if (ident->date_begin && ident->date_end)
		date = parse_timestamp(ident->date_begin, NULL, 10);
	if (date_overflows(date))
		date = 0;
	else {
		if (ident->tz_begin && ident->tz_end)
			tz = strtol(ident->tz_begin, NULL, 10);
		if (tz >= INT_MAX || tz <= INT_MIN)
			tz = 0;
	}
	return show_date(date, tz, mode);
}