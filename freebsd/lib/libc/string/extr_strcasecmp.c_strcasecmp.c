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

/* Variables and functions */
 int /*<<< orphan*/  __get_locale () ; 
 int strcasecmp_l (char const*,char const*,int /*<<< orphan*/ ) ; 

int
strcasecmp(const char *s1, const char *s2)
{
	return strcasecmp_l(s1, s2, __get_locale());
}