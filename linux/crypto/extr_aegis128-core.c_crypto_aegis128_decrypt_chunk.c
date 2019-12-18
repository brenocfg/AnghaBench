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
typedef  union aegis_block {int /*<<< orphan*/  const* bytes; } const aegis_block ;
typedef  int /*<<< orphan*/  const u8 ;
struct aegis_state {union aegis_block const* blocks; } ;

/* Variables and functions */
 scalar_t__ AEGIS_ALIGNED (int /*<<< orphan*/  const*) ; 
 unsigned int AEGIS_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_aegis128_update_a (struct aegis_state*,union aegis_block const*) ; 
 int /*<<< orphan*/  crypto_aegis_block_and (union aegis_block const*,union aegis_block const*) ; 
 int /*<<< orphan*/  crypto_aegis_block_xor (union aegis_block const*,union aegis_block const*) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void crypto_aegis128_decrypt_chunk(struct aegis_state *state, u8 *dst,
					  const u8 *src, unsigned int size)
{
	union aegis_block tmp;

	if (AEGIS_ALIGNED(src) && AEGIS_ALIGNED(dst)) {
		while (size >= AEGIS_BLOCK_SIZE) {
			union aegis_block *dst_blk =
					(union aegis_block *)dst;
			const union aegis_block *src_blk =
					(const union aegis_block *)src;

			tmp = state->blocks[2];
			crypto_aegis_block_and(&tmp, &state->blocks[3]);
			crypto_aegis_block_xor(&tmp, &state->blocks[4]);
			crypto_aegis_block_xor(&tmp, &state->blocks[1]);
			crypto_aegis_block_xor(&tmp, src_blk);

			crypto_aegis128_update_a(state, &tmp);

			*dst_blk = tmp;

			size -= AEGIS_BLOCK_SIZE;
			src += AEGIS_BLOCK_SIZE;
			dst += AEGIS_BLOCK_SIZE;
		}
	} else {
		while (size >= AEGIS_BLOCK_SIZE) {
			tmp = state->blocks[2];
			crypto_aegis_block_and(&tmp, &state->blocks[3]);
			crypto_aegis_block_xor(&tmp, &state->blocks[4]);
			crypto_aegis_block_xor(&tmp, &state->blocks[1]);
			crypto_xor(tmp.bytes, src, AEGIS_BLOCK_SIZE);

			crypto_aegis128_update_a(state, &tmp);

			memcpy(dst, tmp.bytes, AEGIS_BLOCK_SIZE);

			size -= AEGIS_BLOCK_SIZE;
			src += AEGIS_BLOCK_SIZE;
			dst += AEGIS_BLOCK_SIZE;
		}
	}

	if (size > 0) {
		union aegis_block msg = {};
		memcpy(msg.bytes, src, size);

		tmp = state->blocks[2];
		crypto_aegis_block_and(&tmp, &state->blocks[3]);
		crypto_aegis_block_xor(&tmp, &state->blocks[4]);
		crypto_aegis_block_xor(&tmp, &state->blocks[1]);
		crypto_aegis_block_xor(&msg, &tmp);

		memset(msg.bytes + size, 0, AEGIS_BLOCK_SIZE - size);

		crypto_aegis128_update_a(state, &msg);

		memcpy(dst, msg.bytes, size);
	}
}