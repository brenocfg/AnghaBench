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
 int /*<<< orphan*/  _mm_cmpeq_epi32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _mm_movemask_epi8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
m128icmp(__m128i a, __m128i b)
{
	__m128i cmp;

	cmp = _mm_cmpeq_epi32(a, b);

	return _mm_movemask_epi8(cmp) == 0xffff;
}