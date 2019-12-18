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
typedef  scalar_t__ int16_t ;

/* Variables and functions */

__attribute__((used)) static void
mixdown(int16_t *src, int16_t *dest, unsigned n)
{
	int16_t *end;

	for (end = dest + n; dest < end; dest++)
		*dest = (int16_t)(((int)*dest - (int)*src++) / 2);
}