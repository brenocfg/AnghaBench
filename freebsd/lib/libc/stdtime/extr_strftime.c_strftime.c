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
 size_t strftime_l (char*,size_t,char const*,struct tm const*,int /*<<< orphan*/ ) ; 

size_t
strftime(char * __restrict s, size_t maxsize, const char * __restrict format,
    const struct tm * __restrict t)
{
	return strftime_l(s, maxsize, format, t, __get_locale());
}