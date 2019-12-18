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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void
build_sym_key_cache(uint32_t *cache, int cache_len)
{
	static const uint8_t key[] = { 0x50, 0x6d };

        uint32_t result = (((uint32_t)key[0]) << 24) |
                (((uint32_t)key[1]) << 16) |
                (((uint32_t)key[0]) << 8)  |
                ((uint32_t)key[1]);

        uint32_t idx = 32;
        int i;

        for (i = 0; i < cache_len; i++, idx++) {
                uint8_t shift = (idx % 8);
                uint32_t bit;

                cache[i] = result;
                bit = ((key[(idx/8) & 1] << shift) & 0x80) ? 1 : 0;
                result = ((result << 1) | bit);
        }
}