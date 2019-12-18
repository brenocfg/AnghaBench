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
struct s390_des_ctx {int /*<<< orphan*/  key; } ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; int /*<<< orphan*/ * iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int DES_BLOCK_SIZE ; 
 unsigned int __ctrblk_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int blkcipher_walk_virt_block (struct blkcipher_desc*,struct blkcipher_walk*,int) ; 
 int /*<<< orphan*/  cpacf_kmctr (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct s390_des_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_inc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ctrblk ; 
 int /*<<< orphan*/  ctrblk_lock ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ctr_desall_crypt(struct blkcipher_desc *desc, unsigned long fc,
			    struct blkcipher_walk *walk)
{
	struct s390_des_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	u8 buf[DES_BLOCK_SIZE], *ctrptr;
	unsigned int n, nbytes;
	int ret, locked;

	locked = mutex_trylock(&ctrblk_lock);

	ret = blkcipher_walk_virt_block(desc, walk, DES_BLOCK_SIZE);
	while ((nbytes = walk->nbytes) >= DES_BLOCK_SIZE) {
		n = DES_BLOCK_SIZE;
		if (nbytes >= 2*DES_BLOCK_SIZE && locked)
			n = __ctrblk_init(ctrblk, walk->iv, nbytes);
		ctrptr = (n > DES_BLOCK_SIZE) ? ctrblk : walk->iv;
		cpacf_kmctr(fc, ctx->key, walk->dst.virt.addr,
			    walk->src.virt.addr, n, ctrptr);
		if (ctrptr == ctrblk)
			memcpy(walk->iv, ctrptr + n - DES_BLOCK_SIZE,
				DES_BLOCK_SIZE);
		crypto_inc(walk->iv, DES_BLOCK_SIZE);
		ret = blkcipher_walk_done(desc, walk, nbytes - n);
	}
	if (locked)
		mutex_unlock(&ctrblk_lock);
	/* final block may be < DES_BLOCK_SIZE, copy only nbytes */
	if (nbytes) {
		cpacf_kmctr(fc, ctx->key, buf, walk->src.virt.addr,
			    DES_BLOCK_SIZE, walk->iv);
		memcpy(walk->dst.virt.addr, buf, nbytes);
		crypto_inc(walk->iv, DES_BLOCK_SIZE);
		ret = blkcipher_walk_done(desc, walk, 0);
	}
	return ret;
}