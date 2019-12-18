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
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 double strtod (char const* const,char**) ; 

__attribute__((used)) static int
evdns_strtotimeval(const char *const str, struct timeval *out)
{
	double d;
	char *endptr;
	d = strtod(str, &endptr);
	if (*endptr) return -1;
	if (d < 0) return -1;
	out->tv_sec = (int) d;
	out->tv_usec = (int) ((d - (int) d)*1000000);
	if (out->tv_sec == 0 && out->tv_usec < 1000) /* less than 1 msec */
		return -1;
	return 0;
}