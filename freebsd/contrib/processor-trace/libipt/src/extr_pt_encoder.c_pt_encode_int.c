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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t *pt_encode_int(uint8_t *pos, uint64_t val, int size)
{
	for (; size; --size, val >>= 8)
		*pos++ = (uint8_t) val;

	return pos;
}