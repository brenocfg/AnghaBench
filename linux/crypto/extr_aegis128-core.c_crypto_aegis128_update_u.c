#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aegis_state {TYPE_1__* blocks; } ;
struct TYPE_2__ {int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AEGIS_BLOCK_SIZE ; 
 scalar_t__ aegis128_do_simd () ; 
 int /*<<< orphan*/  crypto_aegis128_update (struct aegis_state*) ; 
 int /*<<< orphan*/  crypto_aegis128_update_simd (struct aegis_state*,void const*) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypto_aegis128_update_u(struct aegis_state *state, const void *msg)
{
	if (aegis128_do_simd()) {
		crypto_aegis128_update_simd(state, msg);
		return;
	}

	crypto_aegis128_update(state);
	crypto_xor(state->blocks[0].bytes, msg, AEGIS_BLOCK_SIZE);
}