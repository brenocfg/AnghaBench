#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int prev_mask; int prev_pos; } ;
typedef  TYPE_1__ lzma_simple_x86 ;
typedef  scalar_t__ buffer_pos ;

/* Variables and functions */
 scalar_t__ Test86MSByte (int) ; 

__attribute__((used)) static size_t
x86_code(void *simple_ptr, uint32_t now_pos, bool is_encoder,
		uint8_t *buffer, size_t size)
{
	static const bool MASK_TO_ALLOWED_STATUS[8]
		= { true, true, true, false, true, false, false, false };

	static const uint32_t MASK_TO_BIT_NUMBER[8]
			= { 0, 1, 2, 2, 3, 3, 3, 3 };

	lzma_simple_x86 *simple = simple_ptr;
	uint32_t prev_mask = simple->prev_mask;
	uint32_t prev_pos = simple->prev_pos;

	if (size < 5)
		return 0;

	if (now_pos - prev_pos > 5)
		prev_pos = now_pos - 5;

	const size_t limit = size - 5;
	size_t buffer_pos = 0;

	while (buffer_pos <= limit) {
		uint8_t b = buffer[buffer_pos];
		if (b != 0xE8 && b != 0xE9) {
			++buffer_pos;
			continue;
		}

		const uint32_t offset = now_pos + (uint32_t)(buffer_pos)
				- prev_pos;
		prev_pos = now_pos + (uint32_t)(buffer_pos);

		if (offset > 5) {
			prev_mask = 0;
		} else {
			for (uint32_t i = 0; i < offset; ++i) {
				prev_mask &= 0x77;
				prev_mask <<= 1;
			}
		}

		b = buffer[buffer_pos + 4];

		if (Test86MSByte(b)
			&& MASK_TO_ALLOWED_STATUS[(prev_mask >> 1) & 0x7]
				&& (prev_mask >> 1) < 0x10) {

			uint32_t src = ((uint32_t)(b) << 24)
				| ((uint32_t)(buffer[buffer_pos + 3]) << 16)
				| ((uint32_t)(buffer[buffer_pos + 2]) << 8)
				| (buffer[buffer_pos + 1]);

			uint32_t dest;
			while (true) {
				if (is_encoder)
					dest = src + (now_pos + (uint32_t)(
							buffer_pos) + 5);
				else
					dest = src - (now_pos + (uint32_t)(
							buffer_pos) + 5);

				if (prev_mask == 0)
					break;

				const uint32_t i = MASK_TO_BIT_NUMBER[
						prev_mask >> 1];

				b = (uint8_t)(dest >> (24 - i * 8));

				if (!Test86MSByte(b))
					break;

				src = dest ^ ((1 << (32 - i * 8)) - 1);
			}

			buffer[buffer_pos + 4]
					= (uint8_t)(~(((dest >> 24) & 1) - 1));
			buffer[buffer_pos + 3] = (uint8_t)(dest >> 16);
			buffer[buffer_pos + 2] = (uint8_t)(dest >> 8);
			buffer[buffer_pos + 1] = (uint8_t)(dest);
			buffer_pos += 5;
			prev_mask = 0;

		} else {
			++buffer_pos;
			prev_mask |= 1;
			if (Test86MSByte(b))
				prev_mask |= 0x10;
		}
	}

	simple->prev_mask = prev_mask;
	simple->prev_pos = prev_pos;

	return buffer_pos;
}