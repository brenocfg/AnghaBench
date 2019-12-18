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
 int /*<<< orphan*/  _mm_clmulepi64_si128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_or_si128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_shuffle_epi32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_slli_epi32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_slli_si128 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_srli_epi32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_srli_si128 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_xor_si128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reduce4(__m128i H1, __m128i H2, __m128i H3, __m128i H4,
    __m128i X1, __m128i X2, __m128i X3, __m128i X4, __m128i *res)
{
	/*algorithm by Krzysztof Jankowski, Pierre Laurent - Intel*/
	__m128i H1_X1_lo, H1_X1_hi, H2_X2_lo, H2_X2_hi, H3_X3_lo,
	    H3_X3_hi, H4_X4_lo, H4_X4_hi, lo, hi;
	__m128i tmp0, tmp1, tmp2, tmp3;
	__m128i tmp4, tmp5, tmp6, tmp7;
	__m128i tmp8, tmp9;

	H1_X1_lo = _mm_clmulepi64_si128(H1, X1, 0x00);
	H2_X2_lo = _mm_clmulepi64_si128(H2, X2, 0x00);
	H3_X3_lo = _mm_clmulepi64_si128(H3, X3, 0x00);
	H4_X4_lo = _mm_clmulepi64_si128(H4, X4, 0x00);

	lo = _mm_xor_si128(H1_X1_lo, H2_X2_lo);
	lo = _mm_xor_si128(lo, H3_X3_lo);
	lo = _mm_xor_si128(lo, H4_X4_lo);

	H1_X1_hi = _mm_clmulepi64_si128(H1, X1, 0x11);
	H2_X2_hi = _mm_clmulepi64_si128(H2, X2, 0x11);
	H3_X3_hi = _mm_clmulepi64_si128(H3, X3, 0x11);
	H4_X4_hi = _mm_clmulepi64_si128(H4, X4, 0x11);

	hi = _mm_xor_si128(H1_X1_hi, H2_X2_hi);
	hi = _mm_xor_si128(hi, H3_X3_hi);
	hi = _mm_xor_si128(hi, H4_X4_hi);

	tmp0 = _mm_shuffle_epi32(H1, 78);
	tmp4 = _mm_shuffle_epi32(X1, 78);
	tmp0 = _mm_xor_si128(tmp0, H1);
	tmp4 = _mm_xor_si128(tmp4, X1);
	tmp1 = _mm_shuffle_epi32(H2, 78);
	tmp5 = _mm_shuffle_epi32(X2, 78);
	tmp1 = _mm_xor_si128(tmp1, H2);
	tmp5 = _mm_xor_si128(tmp5, X2);
	tmp2 = _mm_shuffle_epi32(H3, 78);
	tmp6 = _mm_shuffle_epi32(X3, 78);
	tmp2 = _mm_xor_si128(tmp2, H3);
	tmp6 = _mm_xor_si128(tmp6, X3);
	tmp3 = _mm_shuffle_epi32(H4, 78);
	tmp7 = _mm_shuffle_epi32(X4, 78);
	tmp3 = _mm_xor_si128(tmp3, H4);
	tmp7 = _mm_xor_si128(tmp7, X4);

	tmp0 = _mm_clmulepi64_si128(tmp0, tmp4, 0x00);
	tmp1 = _mm_clmulepi64_si128(tmp1, tmp5, 0x00);
	tmp2 = _mm_clmulepi64_si128(tmp2, tmp6, 0x00);
	tmp3 = _mm_clmulepi64_si128(tmp3, tmp7, 0x00);

	tmp0 = _mm_xor_si128(tmp0, lo);
	tmp0 = _mm_xor_si128(tmp0, hi);
	tmp0 = _mm_xor_si128(tmp1, tmp0);
	tmp0 = _mm_xor_si128(tmp2, tmp0);
	tmp0 = _mm_xor_si128(tmp3, tmp0);

	tmp4 = _mm_slli_si128(tmp0, 8);
	tmp0 = _mm_srli_si128(tmp0, 8);

	lo = _mm_xor_si128(tmp4, lo);
	hi = _mm_xor_si128(tmp0, hi);

	tmp3 = lo;
	tmp6 = hi;

	tmp7 = _mm_srli_epi32(tmp3, 31);
	tmp8 = _mm_srli_epi32(tmp6, 31);
	tmp3 = _mm_slli_epi32(tmp3, 1);
	tmp6 = _mm_slli_epi32(tmp6, 1);

	tmp9 = _mm_srli_si128(tmp7, 12);
	tmp8 = _mm_slli_si128(tmp8, 4);
	tmp7 = _mm_slli_si128(tmp7, 4);
	tmp3 = _mm_or_si128(tmp3, tmp7);
	tmp6 = _mm_or_si128(tmp6, tmp8);
	tmp6 = _mm_or_si128(tmp6, tmp9);

	tmp7 = _mm_slli_epi32(tmp3, 31);
	tmp8 = _mm_slli_epi32(tmp3, 30);
	tmp9 = _mm_slli_epi32(tmp3, 25);

	tmp7 = _mm_xor_si128(tmp7, tmp8);
	tmp7 = _mm_xor_si128(tmp7, tmp9);
	tmp8 = _mm_srli_si128(tmp7, 4);
	tmp7 = _mm_slli_si128(tmp7, 12);
	tmp3 = _mm_xor_si128(tmp3, tmp7);

	tmp2 = _mm_srli_epi32(tmp3, 1);
	tmp4 = _mm_srli_epi32(tmp3, 2);
	tmp5 = _mm_srli_epi32(tmp3, 7);
	tmp2 = _mm_xor_si128(tmp2, tmp4);
	tmp2 = _mm_xor_si128(tmp2, tmp5);
	tmp2 = _mm_xor_si128(tmp2, tmp8);
	tmp3 = _mm_xor_si128(tmp3, tmp2);
	tmp6 = _mm_xor_si128(tmp6, tmp3);

	*res = tmp6;
}