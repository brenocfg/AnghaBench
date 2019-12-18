#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int low; scalar_t__ cache_size; int cache; } ;
typedef  TYPE_1__ lzma_range_encoder ;

/* Variables and functions */
 int RC_SHIFT_BITS ; 

__attribute__((used)) static inline bool
rc_shift_low(lzma_range_encoder *rc,
		uint8_t *out, size_t *out_pos, size_t out_size)
{
	if ((uint32_t)(rc->low) < (uint32_t)(0xFF000000)
			|| (uint32_t)(rc->low >> 32) != 0) {
		do {
			if (*out_pos == out_size)
				return true;

			out[*out_pos] = rc->cache + (uint8_t)(rc->low >> 32);
			++*out_pos;
			rc->cache = 0xFF;

		} while (--rc->cache_size != 0);

		rc->cache = (rc->low >> 24) & 0xFF;
	}

	++rc->cache_size;
	rc->low = (rc->low & 0x00FFFFFF) << RC_SHIFT_BITS;

	return false;
}