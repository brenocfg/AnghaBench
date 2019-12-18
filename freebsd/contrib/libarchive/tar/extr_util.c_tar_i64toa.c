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
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */

const char *
tar_i64toa(int64_t n0)
{
	static char buff[24];
	uint64_t n = n0 < 0 ? -n0 : n0;
	char *p = buff + sizeof(buff);

	*--p = '\0';
	do {
		*--p = '0' + (int)(n % 10);
	} while (n /= 10);
	if (n0 < 0)
		*--p = '-';
	return p;
}