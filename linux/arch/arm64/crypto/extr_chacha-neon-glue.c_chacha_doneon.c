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
typedef  int u32 ;

/* Variables and functions */
 int CHACHA_BLOCK_SIZE ; 
 int /*<<< orphan*/  chacha_4block_xor_neon (int*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  chacha_block_xor_neon (int*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int min (int,int) ; 

__attribute__((used)) static void chacha_doneon(u32 *state, u8 *dst, const u8 *src,
			  int bytes, int nrounds)
{
	while (bytes > 0) {
		int l = min(bytes, CHACHA_BLOCK_SIZE * 5);

		if (l <= CHACHA_BLOCK_SIZE) {
			u8 buf[CHACHA_BLOCK_SIZE];

			memcpy(buf, src, l);
			chacha_block_xor_neon(state, buf, buf, nrounds);
			memcpy(dst, buf, l);
			state[12] += 1;
			break;
		}
		chacha_4block_xor_neon(state, dst, src, nrounds, l);
		bytes -= CHACHA_BLOCK_SIZE * 5;
		src += CHACHA_BLOCK_SIZE * 5;
		dst += CHACHA_BLOCK_SIZE * 5;
		state[12] += 5;
	}
}