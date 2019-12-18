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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int KEY_CACHE_LEN ; 
 int /*<<< orphan*/  build_sym_key_cache (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
build_byte_cache(uint32_t byte_cache[256][4])
{
#define KEY_CACHE_LEN			96
	int i, j, k;
	uint32_t key_cache[KEY_CACHE_LEN];

	build_sym_key_cache(key_cache, KEY_CACHE_LEN);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 256; j++) {
			uint8_t b = j;
			byte_cache[j][i] = 0;
			for (k = 0; k < 8; k++) {
				if (b & 0x80)
					byte_cache[j][i] ^= key_cache[8 * i + k];
				b <<= 1U;
			}
		}
	}
}