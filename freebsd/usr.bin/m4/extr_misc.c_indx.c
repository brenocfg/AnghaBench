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
typedef  int ptrdiff_t ;

/* Variables and functions */
 char* strstr (char const*,char const*) ; 

ptrdiff_t
indx(const char *s1, const char *s2)
{
	char *t;

	t = strstr(s1, s2);
	if (t == NULL)
		return (-1);
	else
		return (t - s1);
}