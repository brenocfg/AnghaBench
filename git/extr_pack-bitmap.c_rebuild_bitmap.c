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
typedef  size_t uint32_t ;
struct ewah_iterator {int dummy; } ;
struct ewah_bitmap {int dummy; } ;
struct bitmap {int dummy; } ;
typedef  size_t eword_t ;

/* Variables and functions */
 size_t BITS_IN_EWORD ; 
 int /*<<< orphan*/  bitmap_set (struct bitmap*,size_t) ; 
 scalar_t__ ewah_bit_ctz64 (size_t) ; 
 int /*<<< orphan*/  ewah_iterator_init (struct ewah_iterator*,struct ewah_bitmap*) ; 
 scalar_t__ ewah_iterator_next (size_t*,struct ewah_iterator*) ; 

__attribute__((used)) static int rebuild_bitmap(uint32_t *reposition,
			  struct ewah_bitmap *source,
			  struct bitmap *dest)
{
	uint32_t pos = 0;
	struct ewah_iterator it;
	eword_t word;

	ewah_iterator_init(&it, source);

	while (ewah_iterator_next(&word, &it)) {
		uint32_t offset, bit_pos;

		for (offset = 0; offset < BITS_IN_EWORD; ++offset) {
			if ((word >> offset) == 0)
				break;

			offset += ewah_bit_ctz64(word >> offset);

			bit_pos = reposition[pos + offset];
			if (bit_pos > 0)
				bitmap_set(dest, bit_pos - 1);
			else /* can't reuse, we don't have the object */
				return -1;
		}

		pos += BITS_IN_EWORD;
	}
	return 0;
}