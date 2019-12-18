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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int __m128i ;

/* Variables and functions */
 int _mm_loadu_si128 (int const*) ; 
 int /*<<< orphan*/  _mm_storeu_si128 (int*,int) ; 
 int aesni_dec (int,int const*,int) ; 
 int aesni_enc (int,int const*,int) ; 
 int xts_crank_lfsr (int) ; 

__attribute__((used)) static void
aesni_crypt_xts_block(int rounds, const __m128i *key_schedule, __m128i *tweak,
    const uint8_t *from, uint8_t *to, int do_encrypt)
{
	__m128i block;

	block = _mm_loadu_si128((const __m128i *)from) ^ *tweak;

	if (do_encrypt)
		block = aesni_enc(rounds - 1, key_schedule, block);
	else
		block = aesni_dec(rounds - 1, key_schedule, block);

	_mm_storeu_si128((__m128i *)to, block ^ *tweak);

	*tweak = xts_crank_lfsr(*tweak);
}