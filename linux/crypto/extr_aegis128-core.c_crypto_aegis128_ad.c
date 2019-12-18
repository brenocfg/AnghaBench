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
typedef  int /*<<< orphan*/  u8 ;
struct aegis_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ AEGIS_ALIGNED (int /*<<< orphan*/  const*) ; 
 unsigned int AEGIS_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_aegis128_update_a (struct aegis_state*,union aegis_block const*) ; 
 int /*<<< orphan*/  crypto_aegis128_update_u (struct aegis_state*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void crypto_aegis128_ad(struct aegis_state *state,
			       const u8 *src, unsigned int size)
{
	if (AEGIS_ALIGNED(src)) {
		const union aegis_block *src_blk =
				(const union aegis_block *)src;

		while (size >= AEGIS_BLOCK_SIZE) {
			crypto_aegis128_update_a(state, src_blk);

			size -= AEGIS_BLOCK_SIZE;
			src_blk++;
		}
	} else {
		while (size >= AEGIS_BLOCK_SIZE) {
			crypto_aegis128_update_u(state, src);

			size -= AEGIS_BLOCK_SIZE;
			src += AEGIS_BLOCK_SIZE;
		}
	}
}