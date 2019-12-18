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
 int strcoll_l (char const*,char const*,int /*<<< orphan*/ ) ; 

int
strcoll(const char *s, const char *s2)
{
	return strcoll_l(s, s2, __get_locale());
}