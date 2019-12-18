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

__attribute__((used)) static int
getdec(char **ptr)
{
	char *p;
	int ret;

	p = *ptr;
	ret = 0;
	if ((*p < '0') || (*p > '9'))
		return -1;
	while ((*p >= '0') && (*p <= '9')) {
		ret = ret * 10 + (*p - '0');
		p++;
	}
	*ptr = p;
	return ret;
}