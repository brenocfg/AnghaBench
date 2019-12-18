#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  protkey; } ;
struct s390_paes_ctx {unsigned long fc; TYPE_1__ pk; } ;
struct TYPE_9__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_10__ {TYPE_4__ virt; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_2__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; int /*<<< orphan*/ * iv; TYPE_5__ dst; TYPE_3__ src; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 unsigned int EIO ; 
 scalar_t__ __ctr_paes_set_key (struct s390_paes_ctx*) ; 
 unsigned int __ctrblk_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int blkcipher_walk_virt_block (struct blkcipher_desc*,struct blkcipher_walk*,int) ; 
 int cpacf_kmctr (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct s390_paes_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_inc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ctrblk ; 
 int /*<<< orphan*/  ctrblk_lock ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ctr_paes_crypt(struct blkcipher_desc *desc, unsigned long modifier,
			  struct blkcipher_walk *walk)
{
	struct s390_paes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	u8 buf[AES_BLOCK_SIZE], *ctrptr;
	unsigned int nbytes, n, k;
	int ret, locked;

	locked = spin_trylock(&ctrblk_lock);

	ret = blkcipher_walk_virt_block(desc, walk, AES_BLOCK_SIZE);
	while ((nbytes = walk->nbytes) >= AES_BLOCK_SIZE) {
		n = AES_BLOCK_SIZE;
		if (nbytes >= 2*AES_BLOCK_SIZE && locked)
			n = __ctrblk_init(ctrblk, walk->iv, nbytes);
		ctrptr = (n > AES_BLOCK_SIZE) ? ctrblk : walk->iv;
		k = cpacf_kmctr(ctx->fc | modifier, ctx->pk.protkey,
				walk->dst.virt.addr, walk->src.virt.addr,
				n, ctrptr);
		if (k) {
			if (ctrptr == ctrblk)
				memcpy(walk->iv, ctrptr + k - AES_BLOCK_SIZE,
				       AES_BLOCK_SIZE);
			crypto_inc(walk->iv, AES_BLOCK_SIZE);
			ret = blkcipher_walk_done(desc, walk, nbytes - n);
		}
		if (k < n) {
			if (__ctr_paes_set_key(ctx) != 0) {
				if (locked)
					spin_unlock(&ctrblk_lock);
				return blkcipher_walk_done(desc, walk, -EIO);
			}
		}
	}
	if (locked)
		spin_unlock(&ctrblk_lock);
	/*
	 * final block may be < AES_BLOCK_SIZE, copy only nbytes
	 */
	if (nbytes) {
		while (1) {
			if (cpacf_kmctr(ctx->fc | modifier,
					ctx->pk.protkey, buf,
					walk->src.virt.addr, AES_BLOCK_SIZE,
					walk->iv) == AES_BLOCK_SIZE)
				break;
			if (__ctr_paes_set_key(ctx) != 0)
				return blkcipher_walk_done(desc, walk, -EIO);
		}
		memcpy(walk->dst.virt.addr, buf, nbytes);
		crypto_inc(walk->iv, AES_BLOCK_SIZE);
		ret = blkcipher_walk_done(desc, walk, 0);
	}

	return ret;
}