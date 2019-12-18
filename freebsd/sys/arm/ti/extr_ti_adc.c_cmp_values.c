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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static int
cmp_values(const void *a, const void *b)
{
	const uint32_t *v1, *v2;
	v1 = a;
	v2 = b;
	if (*v1 < *v2)
		return -1;
	if (*v1 > *v2)
		return 1;

	return (0);
}