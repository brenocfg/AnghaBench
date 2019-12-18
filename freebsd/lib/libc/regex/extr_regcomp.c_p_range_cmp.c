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
typedef  int wchar_t ;

/* Variables and functions */
 int __wcollate_range_cmp (int,int) ; 
 int wcscoll (int*,int*) ; 

__attribute__((used)) static int
p_range_cmp(wchar_t c1, wchar_t c2)
{
#ifndef LIBREGEX
	return __wcollate_range_cmp(c1, c2);
#else
	/* Copied from libc/collate __wcollate_range_cmp */
	wchar_t s1[2], s2[2];

	s1[0] = c1;
	s1[1] = L'\0';
	s2[0] = c2;
	s2[1] = L'\0';
	return (wcscoll(s1, s2));
#endif
}