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
 int strcoll (char*,char*) ; 

__attribute__((used)) static int
stable_collate_range_cmp(int c1, int c2)
{
	static char s1[2], s2[2];
	int ret;

	s1[0] = c1;
	s2[0] = c2;
	if ((ret = strcoll(s1, s2)) != 0)
		return (ret);
	return (c1 - c2);
}