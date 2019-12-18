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
typedef  int /*<<< orphan*/  const u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int CHACHA_BLOCK_SIZE ; 
 int /*<<< orphan*/  chacha_4block_xor_neon (scalar_t__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  chacha_block_xor_neon (scalar_t__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void chacha_doneon(u32 *state, u8 *dst, const u8 *src,
			  unsigned int bytes, int nrounds)
{
	u8 buf[CHACHA_BLOCK_SIZE];

	while (bytes >= CHACHA_BLOCK_SIZE * 4) {
		chacha_4block_xor_neon(state, dst, src, nrounds);
		bytes -= CHACHA_BLOCK_SIZE * 4;
		src += CHACHA_BLOCK_SIZE * 4;
		dst += CHACHA_BLOCK_SIZE * 4;
		state[12] += 4;
	}
	while (bytes >= CHACHA_BLOCK_SIZE) {
		chacha_block_xor_neon(state, dst, src, nrounds);
		bytes -= CHACHA_BLOCK_SIZE;
		src += CHACHA_BLOCK_SIZE;
		dst += CHACHA_BLOCK_SIZE;
		state[12]++;
	}
	if (bytes) {
		memcpy(buf, src, bytes);
		chacha_block_xor_neon(state, buf, buf, nrounds);
		memcpy(dst, buf, bytes);
	}
}