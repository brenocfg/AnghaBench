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
 int /*<<< orphan*/  _mm_add_epi64 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  _mm_cmpeq_epi64 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  _mm_setr_epi32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_setzero_si128 () ; 
 int /*<<< orphan*/  _mm_sub_epi64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_unpackhi_epi64 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline __m128i
nextc(__m128i x)
{
	const __m128i ONE = _mm_setr_epi32(0, 0, 1, 0);
	const __m128i ZERO = _mm_setzero_si128();

	x = _mm_add_epi64(x, ONE);
	__m128i t = _mm_cmpeq_epi64(x, ZERO);
	t = _mm_unpackhi_epi64(t, ZERO);
	x = _mm_sub_epi64(x, t);

	return x;
}