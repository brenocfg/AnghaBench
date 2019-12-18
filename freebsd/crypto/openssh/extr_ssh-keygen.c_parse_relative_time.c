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
typedef  int u_int64_t ;
typedef  int time_t ;
typedef  int int64_t ;

/* Variables and functions */
 int convtime (char const*) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 

__attribute__((used)) static u_int64_t
parse_relative_time(const char *s, time_t now)
{
	int64_t mul, secs;

	mul = *s == '-' ? -1 : 1;

	if ((secs = convtime(s + 1)) == -1)
		fatal("Invalid relative certificate time %s", s);
	if (mul == -1 && secs > now)
		fatal("Certificate time %s cannot be represented", s);
	return now + (u_int64_t)(secs * mul);
}