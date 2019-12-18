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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static bool memeq(const void *a, const void *b, size_t size)
{
	const uint8_t *x = a;
	const uint8_t *y = b;
	size_t i;

	for (i = 0; i < size; ++i)
		if (x[i] != y[i])
			return false;

	return true;
}