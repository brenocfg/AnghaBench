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
struct scatterlist {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; TYPE_4__ src; TYPE_2__ dst; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;
struct arc4_ctx {int dummy; } ;

/* Variables and functions */
 int ARC4_BLOCK_SIZE ; 
 int /*<<< orphan*/  CRYPTO_DIR_ENCRYPT ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  _deu_arc4_ecb (struct arc4_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 struct arc4_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecb_arc4_encrypt(struct blkcipher_desc *desc,
                           struct scatterlist *dst, struct scatterlist *src,
                           unsigned int nbytes)
{
        struct arc4_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
        struct blkcipher_walk walk;
        int err;

        DPRINTF(1, "\n");
        blkcipher_walk_init(&walk, dst, src, nbytes);
        err = blkcipher_walk_virt(desc, &walk);

        while ((nbytes = walk.nbytes)) {
                _deu_arc4_ecb(ctx, walk.dst.virt.addr, walk.src.virt.addr, 
                               NULL, nbytes, CRYPTO_DIR_ENCRYPT, 0);
                nbytes &= ARC4_BLOCK_SIZE - 1;
                err = blkcipher_walk_done(desc, &walk, nbytes);
        }

        return err;
}