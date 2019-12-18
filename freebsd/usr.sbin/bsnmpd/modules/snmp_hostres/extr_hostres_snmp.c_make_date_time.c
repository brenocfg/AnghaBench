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
typedef  char u_int ;
typedef  char u_char ;
struct tm {int tm_year; char tm_mon; char tm_mday; char tm_hour; char tm_min; char tm_sec; scalar_t__ tm_gmtoff; } ;

/* Variables and functions */
 int labs (scalar_t__) ; 

int
make_date_time(u_char *str, const struct tm *tm, u_int decisecs)
{

	str[0] = (u_char)((tm->tm_year + 1900) >> 8);
	str[1] = (u_char)(tm->tm_year + 1900);
	str[2] = tm->tm_mon + 1;
	str[3] = tm->tm_mday;
	str[4] = tm->tm_hour;
	str[5] = tm->tm_min;
	str[6] = tm->tm_sec;
	str[7] = decisecs;
	if (tm->tm_gmtoff < 0)
		str[8] = '-';
	else
		str[8] = '+';

	str[9] = (u_char)(labs(tm->tm_gmtoff) / 3600);
	str[10] = (u_char)((labs(tm->tm_gmtoff) % 3600) / 60);

	return (11);
}