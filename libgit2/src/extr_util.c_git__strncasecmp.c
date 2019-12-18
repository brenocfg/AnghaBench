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
 scalar_t__ git__tolower (char const) ; 

int git__strncasecmp(const char *a, const char *b, size_t sz)
{
	int al, bl;

	do {
		al = (unsigned char)git__tolower(*a);
		bl = (unsigned char)git__tolower(*b);
		++a, ++b;
	} while (--sz && al && al == bl);

	return al - bl;
}