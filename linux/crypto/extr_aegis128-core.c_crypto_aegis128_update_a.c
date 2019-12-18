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
typedef  union aegis_block {int dummy; } aegis_block ;
struct aegis_state {int /*<<< orphan*/ * blocks; } ;

/* Variables and functions */
 scalar_t__ aegis128_do_simd () ; 
 int /*<<< orphan*/  crypto_aegis128_update (struct aegis_state*) ; 
 int /*<<< orphan*/  crypto_aegis128_update_simd (struct aegis_state*,union aegis_block const*) ; 
 int /*<<< orphan*/  crypto_aegis_block_xor (int /*<<< orphan*/ *,union aegis_block const*) ; 

__attribute__((used)) static void crypto_aegis128_update_a(struct aegis_state *state,
				     const union aegis_block *msg)
{
	if (aegis128_do_simd()) {
		crypto_aegis128_update_simd(state, msg);
		return;
	}

	crypto_aegis128_update(state);
	crypto_aegis_block_xor(&state->blocks[0], msg);
}