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
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  strtol (char const*,char**,int) ; 
 int /*<<< orphan*/  strtoll (char const*,char**,int) ; 

intmax_t gitstrtoimax (const char *nptr, char **endptr, int base)
{
#if defined(NO_STRTOULL)
	return strtol(nptr, endptr, base);
#else
	return strtoll(nptr, endptr, base);
#endif
}