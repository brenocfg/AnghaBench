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

int __collate_range_cmp(char c1, char c2)
{
	char s1[2], s2[2];

	s1[0] = c1;
	s1[1] = '\0';
	s2[0] = c2;
	s2[1] = '\0';
	return (strcoll(s1, s2));
}