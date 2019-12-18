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
typedef  int uint8_t ;
typedef  unsigned int term_color_t ;

/* Variables and functions */
 int /*<<< orphan*/  vga_compute_shifted_pattern (int const*,unsigned int,unsigned int,unsigned int,unsigned int,int*,int*) ; 

__attribute__((used)) static void
vga_copy_bitmap_portion(uint8_t *pattern_2colors, uint8_t *pattern_ncolors,
    const uint8_t *src, const uint8_t *src_mask, unsigned int src_width,
    unsigned int src_x, unsigned int dst_x, unsigned int x_count,
    unsigned int src_y, unsigned int dst_y, unsigned int y_count,
    term_color_t fg, term_color_t bg, int overwrite)
{
	unsigned int i, bytes;
	uint8_t pattern, relevant_bits, mask;

	bytes = (src_width + 7) / 8;

	for (i = 0; i < y_count; ++i) {
		vga_compute_shifted_pattern(src + (src_y + i) * bytes,
		    bytes, src_x, x_count, dst_x, &pattern, &relevant_bits);

		if (src_mask == NULL) {
			/*
			 * No src mask. Consider that all wanted bits
			 * from the source are "authoritative".
			 */
			mask = relevant_bits;
		} else {
			/*
			 * There's an src mask. We shift it the same way
			 * we shifted the source pattern.
			 */
			vga_compute_shifted_pattern(
			    src_mask + (src_y + i) * bytes,
			    bytes, src_x, x_count, dst_x,
			    &mask, NULL);

			/* Now, only keep the wanted bits among them. */
			mask &= relevant_bits;
		}

		/*
		 * Clear bits from the pattern which must be
		 * transparent, according to the source mask.
		 */
		pattern &= mask;

		/* Set the bits in the 2-colors array. */
		if (overwrite)
			pattern_2colors[dst_y + i] &= ~mask;
		pattern_2colors[dst_y + i] |= pattern;

		if (pattern_ncolors == NULL)
			continue;

		/*
		 * Set the same bits in the n-colors array. This one
		 * supports transparency, when a given bit is cleared in
		 * all colors.
		 */
		if (overwrite) {
			/*
			 * Ensure that the pixels used by this bitmap are
			 * cleared in other colors.
			 */
			for (int j = 0; j < 16; ++j)
				pattern_ncolors[(dst_y + i) * 16 + j] &=
				    ~mask;
		}
		pattern_ncolors[(dst_y + i) * 16 + fg] |= pattern;
		pattern_ncolors[(dst_y + i) * 16 + bg] |= (~pattern & mask);
	}
}