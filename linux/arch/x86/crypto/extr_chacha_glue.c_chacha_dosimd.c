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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int CHACHA_BLOCK_SIZE ; 
 int /*<<< orphan*/  chacha_2block_xor_avx2 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int) ; 
 int /*<<< orphan*/  chacha_2block_xor_avx512vl (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int) ; 
 int /*<<< orphan*/  chacha_4block_xor_avx2 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int) ; 
 int /*<<< orphan*/  chacha_4block_xor_avx512vl (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int) ; 
 int /*<<< orphan*/  chacha_4block_xor_ssse3 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int) ; 
 int /*<<< orphan*/  chacha_8block_xor_avx2 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int) ; 
 int /*<<< orphan*/  chacha_8block_xor_avx512vl (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int) ; 
 scalar_t__ chacha_advance (unsigned int,int) ; 
 int /*<<< orphan*/  chacha_block_xor_ssse3 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int) ; 
 scalar_t__ chacha_use_avx2 ; 
 scalar_t__ chacha_use_avx512vl ; 

__attribute__((used)) static void chacha_dosimd(u32 *state, u8 *dst, const u8 *src,
			  unsigned int bytes, int nrounds)
{
#ifdef CONFIG_AS_AVX2
#ifdef CONFIG_AS_AVX512
	if (chacha_use_avx512vl) {
		while (bytes >= CHACHA_BLOCK_SIZE * 8) {
			chacha_8block_xor_avx512vl(state, dst, src, bytes,
						   nrounds);
			bytes -= CHACHA_BLOCK_SIZE * 8;
			src += CHACHA_BLOCK_SIZE * 8;
			dst += CHACHA_BLOCK_SIZE * 8;
			state[12] += 8;
		}
		if (bytes > CHACHA_BLOCK_SIZE * 4) {
			chacha_8block_xor_avx512vl(state, dst, src, bytes,
						   nrounds);
			state[12] += chacha_advance(bytes, 8);
			return;
		}
		if (bytes > CHACHA_BLOCK_SIZE * 2) {
			chacha_4block_xor_avx512vl(state, dst, src, bytes,
						   nrounds);
			state[12] += chacha_advance(bytes, 4);
			return;
		}
		if (bytes) {
			chacha_2block_xor_avx512vl(state, dst, src, bytes,
						   nrounds);
			state[12] += chacha_advance(bytes, 2);
			return;
		}
	}
#endif
	if (chacha_use_avx2) {
		while (bytes >= CHACHA_BLOCK_SIZE * 8) {
			chacha_8block_xor_avx2(state, dst, src, bytes, nrounds);
			bytes -= CHACHA_BLOCK_SIZE * 8;
			src += CHACHA_BLOCK_SIZE * 8;
			dst += CHACHA_BLOCK_SIZE * 8;
			state[12] += 8;
		}
		if (bytes > CHACHA_BLOCK_SIZE * 4) {
			chacha_8block_xor_avx2(state, dst, src, bytes, nrounds);
			state[12] += chacha_advance(bytes, 8);
			return;
		}
		if (bytes > CHACHA_BLOCK_SIZE * 2) {
			chacha_4block_xor_avx2(state, dst, src, bytes, nrounds);
			state[12] += chacha_advance(bytes, 4);
			return;
		}
		if (bytes > CHACHA_BLOCK_SIZE) {
			chacha_2block_xor_avx2(state, dst, src, bytes, nrounds);
			state[12] += chacha_advance(bytes, 2);
			return;
		}
	}
#endif
	while (bytes >= CHACHA_BLOCK_SIZE * 4) {
		chacha_4block_xor_ssse3(state, dst, src, bytes, nrounds);
		bytes -= CHACHA_BLOCK_SIZE * 4;
		src += CHACHA_BLOCK_SIZE * 4;
		dst += CHACHA_BLOCK_SIZE * 4;
		state[12] += 4;
	}
	if (bytes > CHACHA_BLOCK_SIZE) {
		chacha_4block_xor_ssse3(state, dst, src, bytes, nrounds);
		state[12] += chacha_advance(bytes, 4);
		return;
	}
	if (bytes) {
		chacha_block_xor_ssse3(state, dst, src, bytes, nrounds);
		state[12]++;
	}
}