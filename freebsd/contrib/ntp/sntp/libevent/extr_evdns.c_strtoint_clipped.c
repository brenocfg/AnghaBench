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
 int strtoint (char const* const) ; 

__attribute__((used)) static int
strtoint_clipped(const char *const str, int min, int max)
{
	int r = strtoint(str);
	if (r == -1)
		return r;
	else if (r<min)
		return min;
	else if (r>max)
		return max;
	else
		return r;
}