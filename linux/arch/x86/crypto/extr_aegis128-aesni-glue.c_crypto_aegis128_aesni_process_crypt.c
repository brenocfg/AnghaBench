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
struct skcipher_walk {int nbytes; TYPE_4__ dst; TYPE_2__ src; } ;
struct aegis_state {int dummy; } ;
struct aegis_crypt_ops {int /*<<< orphan*/  (* crypt_tail ) (struct aegis_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* crypt_blocks ) (struct aegis_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AEGIS128_BLOCK_SIZE ; 
 int /*<<< orphan*/  round_down (int,int) ; 
 int /*<<< orphan*/  skcipher_walk_done (struct skcipher_walk*,int) ; 
 int /*<<< orphan*/  stub1 (struct aegis_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct aegis_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypto_aegis128_aesni_process_crypt(
		struct aegis_state *state, struct skcipher_walk *walk,
		const struct aegis_crypt_ops *ops)
{
	while (walk->nbytes >= AEGIS128_BLOCK_SIZE) {
		ops->crypt_blocks(state,
				  round_down(walk->nbytes, AEGIS128_BLOCK_SIZE),
				  walk->src.virt.addr, walk->dst.virt.addr);
		skcipher_walk_done(walk, walk->nbytes % AEGIS128_BLOCK_SIZE);
	}

	if (walk->nbytes) {
		ops->crypt_tail(state, walk->nbytes, walk->src.virt.addr,
				walk->dst.virt.addr);
		skcipher_walk_done(walk, 0);
	}
}