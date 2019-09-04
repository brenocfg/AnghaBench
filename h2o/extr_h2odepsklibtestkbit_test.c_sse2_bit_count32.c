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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_add_epi32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_and_si128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_load_si128 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _mm_set_epi32 (unsigned int const,unsigned int const,unsigned int const,unsigned int const) ; 
 int /*<<< orphan*/  _mm_srli_epi32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_store_si128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_xor_si128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t sse2_bit_count32(const __m128i* block, const __m128i* block_end)
{
    const unsigned mu1 = 0x55555555;
    const unsigned mu2 = 0x33333333;
    const unsigned mu3 = 0x0F0F0F0F;
    const unsigned mu4 = 0x0000003F;

	uint32_t tcnt[4];

    // Loading masks
    __m128i m1 = _mm_set_epi32 (mu1, mu1, mu1, mu1);
    __m128i m2 = _mm_set_epi32 (mu2, mu2, mu2, mu2);
    __m128i m3 = _mm_set_epi32 (mu3, mu3, mu3, mu3);
    __m128i m4 = _mm_set_epi32 (mu4, mu4, mu4, mu4);
    __m128i mcnt;
    mcnt = _mm_xor_si128(m1, m1); // cnt = 0

    __m128i tmp1, tmp2;
    do
    {        
        __m128i b = _mm_load_si128(block);
        ++block;

        // b = (b & 0x55555555) + (b >> 1 & 0x55555555);
        tmp1 = _mm_srli_epi32(b, 1);                    // tmp1 = (b >> 1 & 0x55555555)
        tmp1 = _mm_and_si128(tmp1, m1); 
        tmp2 = _mm_and_si128(b, m1);                    // tmp2 = (b & 0x55555555)
        b    = _mm_add_epi32(tmp1, tmp2);               //  b = tmp1 + tmp2

        // b = (b & 0x33333333) + (b >> 2 & 0x33333333);
        tmp1 = _mm_srli_epi32(b, 2);                    // (b >> 2 & 0x33333333)
        tmp1 = _mm_and_si128(tmp1, m2); 
        tmp2 = _mm_and_si128(b, m2);                    // (b & 0x33333333)
        b    = _mm_add_epi32(tmp1, tmp2);               // b = tmp1 + tmp2

        // b = (b + (b >> 4)) & 0x0F0F0F0F;
        tmp1 = _mm_srli_epi32(b, 4);                    // tmp1 = b >> 4
        b = _mm_add_epi32(b, tmp1);                     // b = b + (b >> 4)
        b = _mm_and_si128(b, m3);                       //           & 0x0F0F0F0F

        // b = b + (b >> 8);
        tmp1 = _mm_srli_epi32 (b, 8);                   // tmp1 = b >> 8
        b = _mm_add_epi32(b, tmp1);                     // b = b + (b >> 8)

        // b = (b + (b >> 16)) & 0x0000003F;
        tmp1 = _mm_srli_epi32 (b, 16);                  // b >> 16
        b = _mm_add_epi32(b, tmp1);                     // b + (b >> 16)
        b = _mm_and_si128(b, m4);                       // (b >> 16) & 0x0000003F;

        mcnt = _mm_add_epi32(mcnt, b);                  // mcnt += b

    } while (block < block_end);

    _mm_store_si128((__m128i*)tcnt, mcnt);

    return tcnt[0] + tcnt[1] + tcnt[2] + tcnt[3];
}