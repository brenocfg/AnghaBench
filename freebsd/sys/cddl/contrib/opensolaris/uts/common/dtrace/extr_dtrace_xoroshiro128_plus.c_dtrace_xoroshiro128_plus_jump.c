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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_xoroshiro128_plus_next (int* const) ; 

void
dtrace_xoroshiro128_plus_jump(uint64_t * const state,
	uint64_t * const jump_state)
{
	static const uint64_t JUMP[] = { 0xbeac0467eba5facb,
		0xd86b048b86aa9922 };

	uint64_t s0 = 0;
	uint64_t s1 = 0;
	int i = 0;
	int b = 0;
	for (i = 0; i < sizeof JUMP / sizeof *JUMP; i++) {
		for (b = 0; b < 64; b++) {
			if (JUMP[i] & 1ULL << b) {
				s0 ^= state[0];
				s1 ^= state[1];
			}
			dtrace_xoroshiro128_plus_next(state);
		}
	}
	jump_state[0] = s0;
	jump_state[1] = s1;
}