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
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int /*<<< orphan*/  AESNI_ENC (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  _mm_xor_si128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __m128i
xor_and_encrypt(__m128i a, __m128i b, const unsigned char *k, int nr)
{
	__m128i retval = _mm_xor_si128(a, b);

	retval = AESNI_ENC(retval, k, nr);
	return (retval);
}