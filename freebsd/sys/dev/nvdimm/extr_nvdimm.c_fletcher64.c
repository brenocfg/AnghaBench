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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t
fletcher64(const void *data, size_t length)
{
	size_t i;
	uint32_t a, b;
	const uint32_t *d;

	a = 0;
	b = 0;
	d = (const uint32_t *)data;
	length = length / sizeof(uint32_t);
	for (i = 0; i < length; i++) {
		a += d[i];
		b += a;
	}
	return ((uint64_t)b << 32 | a);
}