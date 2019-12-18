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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  _TRUNCATE ; 
 int _vsnprintf_s (char*,size_t,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
pcap_vsnprintf(char *str, size_t str_size, const char *format, va_list args)
{
	int ret;

	ret = _vsnprintf_s(str, str_size, _TRUNCATE, format, args);

	/*
	 * XXX - _vsnprintf() and _snprintf() do *not* guarantee
	 * that str is null-terminated, but C99's vsnprintf()
	 * and snprintf() do, and we want to offer C99 behavior,
	 * so forcibly null-terminate the string.
	 */
	str[str_size - 1] = '\0';
	return (ret);
}