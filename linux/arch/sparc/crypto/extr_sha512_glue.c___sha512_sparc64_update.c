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
struct sha512_state {unsigned int* count; int /*<<< orphan*/  const* buf; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 unsigned int SHA512_BLOCK_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  sha512_sparc64_transform (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int const) ; 

__attribute__((used)) static void __sha512_sparc64_update(struct sha512_state *sctx, const u8 *data,
				    unsigned int len, unsigned int partial)
{
	unsigned int done = 0;

	if ((sctx->count[0] += len) < len)
		sctx->count[1]++;
	if (partial) {
		done = SHA512_BLOCK_SIZE - partial;
		memcpy(sctx->buf + partial, data, done);
		sha512_sparc64_transform(sctx->state, sctx->buf, 1);
	}
	if (len - done >= SHA512_BLOCK_SIZE) {
		const unsigned int rounds = (len - done) / SHA512_BLOCK_SIZE;

		sha512_sparc64_transform(sctx->state, data + done, rounds);
		done += rounds * SHA512_BLOCK_SIZE;
	}

	memcpy(sctx->buf, data + done, len - done);
}