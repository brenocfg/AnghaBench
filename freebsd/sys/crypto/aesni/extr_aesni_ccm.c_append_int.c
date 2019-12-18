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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */

__attribute__((used)) static void
append_int(size_t value, __m128i *block, size_t offset)
{
	int indx = sizeof(*block) - 1;
	uint8_t *bp = (uint8_t*)block;

	while (indx > (sizeof(*block) - offset)) {
		bp[indx] = value & 0xff;
		indx--;
		value >>= 8;
	}
}