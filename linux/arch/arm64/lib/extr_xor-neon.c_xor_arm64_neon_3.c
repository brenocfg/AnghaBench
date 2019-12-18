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
typedef  int /*<<< orphan*/  uint64x2_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  veorq_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vld1q_u64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vst1q_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void xor_arm64_neon_3(unsigned long bytes, unsigned long *p1,
	unsigned long *p2, unsigned long *p3)
{
	uint64_t *dp1 = (uint64_t *)p1;
	uint64_t *dp2 = (uint64_t *)p2;
	uint64_t *dp3 = (uint64_t *)p3;

	register uint64x2_t v0, v1, v2, v3;
	long lines = bytes / (sizeof(uint64x2_t) * 4);

	do {
		/* p1 ^= p2 */
		v0 = veorq_u64(vld1q_u64(dp1 +  0), vld1q_u64(dp2 +  0));
		v1 = veorq_u64(vld1q_u64(dp1 +  2), vld1q_u64(dp2 +  2));
		v2 = veorq_u64(vld1q_u64(dp1 +  4), vld1q_u64(dp2 +  4));
		v3 = veorq_u64(vld1q_u64(dp1 +  6), vld1q_u64(dp2 +  6));

		/* p1 ^= p3 */
		v0 = veorq_u64(v0, vld1q_u64(dp3 +  0));
		v1 = veorq_u64(v1, vld1q_u64(dp3 +  2));
		v2 = veorq_u64(v2, vld1q_u64(dp3 +  4));
		v3 = veorq_u64(v3, vld1q_u64(dp3 +  6));

		/* store */
		vst1q_u64(dp1 +  0, v0);
		vst1q_u64(dp1 +  2, v1);
		vst1q_u64(dp1 +  4, v2);
		vst1q_u64(dp1 +  6, v3);

		dp1 += 8;
		dp2 += 8;
		dp3 += 8;
	} while (--lines > 0);
}