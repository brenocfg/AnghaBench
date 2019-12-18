#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; unsigned int total; TYPE_4__ src; TYPE_2__ dst; int /*<<< orphan*/  stride; } ;
struct skcipher_request {int dummy; } ;
struct chacha_ctx {int /*<<< orphan*/  nrounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  chacha_doneon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_chacha_init (int /*<<< orphan*/ *,struct chacha_ctx const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 unsigned int round_down (unsigned int,int /*<<< orphan*/ ) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int chacha_neon_stream_xor(struct skcipher_request *req,
				  const struct chacha_ctx *ctx, const u8 *iv)
{
	struct skcipher_walk walk;
	u32 state[16];
	int err;

	err = skcipher_walk_virt(&walk, req, false);

	crypto_chacha_init(state, ctx, iv);

	while (walk.nbytes > 0) {
		unsigned int nbytes = walk.nbytes;

		if (nbytes < walk.total)
			nbytes = round_down(nbytes, walk.stride);

		kernel_neon_begin();
		chacha_doneon(state, walk.dst.virt.addr, walk.src.virt.addr,
			      nbytes, ctx->nrounds);
		kernel_neon_end();
		err = skcipher_walk_done(&walk, walk.nbytes - nbytes);
	}

	return err;
}