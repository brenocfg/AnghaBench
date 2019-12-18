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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int BYTES_PER_WORD ; 
 int /*<<< orphan*/  swap_bits_in_byte (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void swap_words_in_key_and_bits_in_byte(const u8 *in,
						      u8 *out, u32 len)
{
	unsigned int i = 0;
	int j;
	int index = 0;

	j = len - BYTES_PER_WORD;
	while (j >= 0) {
		for (i = 0; i < BYTES_PER_WORD; i++) {
			index = len - j - BYTES_PER_WORD + i;
			out[j + i] =
				swap_bits_in_byte(in[index]);
		}
		j -= BYTES_PER_WORD;
	}
}