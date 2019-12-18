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
 int strcasecmp (char const*,char const*) ; 

__attribute__((used)) static int
compare_names(const void *vp1, const void *vp2)
{
	const char	*cp1, *cp2;
	int		 diff;

	cp1 = *(const char * const *)vp1;
	cp2 = *(const char * const *)vp2;
	return (diff = *cp2 - *cp1) ? diff :
	    strcasecmp(cp1 + 1, cp2 + 1);
}