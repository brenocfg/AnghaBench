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
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 long strtol_l (char const*,char**,int,int /*<<< orphan*/ ) ; 

long
atol_l(const char *str, locale_t locale)
{
	return strtol_l(str, (char **)NULL, 10, locale);
}