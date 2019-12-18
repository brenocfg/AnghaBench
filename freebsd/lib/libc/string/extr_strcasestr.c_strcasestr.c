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
 char* strcasestr_l (char const*,char const*,int /*<<< orphan*/ ) ; 

char *
strcasestr(const char *s, const char *find)
{
	return strcasestr_l(s, find, __get_locale());
}