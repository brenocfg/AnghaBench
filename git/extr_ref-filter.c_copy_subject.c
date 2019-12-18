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
 char* xmemdupz (char const*,unsigned long) ; 

__attribute__((used)) static char *copy_subject(const char *buf, unsigned long len)
{
	char *r = xmemdupz(buf, len);
	int i;

	for (i = 0; i < len; i++)
		if (r[i] == '\n')
			r[i] = ' ';

	return r;
}