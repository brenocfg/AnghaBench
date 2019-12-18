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
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __get_locale () ; 
 char* strptime_l (char const*,char const*,struct tm*,int /*<<< orphan*/ ) ; 

char *
strptime(const char * __restrict buf, const char * __restrict fmt,
    struct tm * __restrict tm)
{
	return strptime_l(buf, fmt, tm, __get_locale());
}