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
 int xdl_recmatch (char const*,long,char const*,long,long) ; 

int xdiff_compare_lines(const char *l1, long s1,
			const char *l2, long s2, long flags)
{
	return xdl_recmatch(l1, s1, l2, s2, flags);
}