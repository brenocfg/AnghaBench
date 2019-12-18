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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  localtime_r (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/  strftime (char*,size_t,char*,struct tm*) ; 

void
format_absolute_time(uint64_t t, char *buf, size_t len)
{
	time_t tt = t > INT_MAX ? INT_MAX : t; /* XXX revisit in 2038 :P */
	struct tm tm;

	localtime_r(&tt, &tm);
	strftime(buf, len, "%Y-%m-%dT%H:%M:%S", &tm);
}