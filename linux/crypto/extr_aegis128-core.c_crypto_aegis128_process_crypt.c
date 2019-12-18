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
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {int nbytes; unsigned int total; TYPE_4__ src; TYPE_2__ dst; int /*<<< orphan*/  stride; } ;
struct aegis_state {int dummy; } ;
struct aegis128_ops {int /*<<< orphan*/  (* crypt_chunk ) (struct aegis_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  (* skcipher_walk_init ) (struct skcipher_walk*,struct aead_request*,int) ;} ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 unsigned int round_down (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct skcipher_walk*,struct aead_request*,int) ; 
 int /*<<< orphan*/  stub2 (struct aegis_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void crypto_aegis128_process_crypt(struct aegis_state *state,
					  struct aead_request *req,
					  const struct aegis128_ops *ops)
{
	struct skcipher_walk walk;

	ops->skcipher_walk_init(&walk, req, false);

	while (walk.nbytes) {
		unsigned int nbytes = walk.nbytes;

		if (nbytes < walk.total)
			nbytes = round_down(nbytes, walk.stride);

		ops->crypt_chunk(state, walk.dst.virt.addr, walk.src.virt.addr,
				 nbytes);

		skcipher_walk_done(&walk, walk.nbytes - nbytes);
	}
}