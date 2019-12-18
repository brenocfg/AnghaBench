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
struct scatterlist {int dummy; } ;
struct des_ctx {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; TYPE_4__ src; TYPE_2__ dst; int /*<<< orphan*/ * iv; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DIR_ENCRYPT ; 
 unsigned int DES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 struct des_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifx_deu_des_cbc (struct des_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cbc_des_encrypt(struct blkcipher_desc *desc,
                    struct scatterlist *dst, struct scatterlist *src,
                    unsigned int nbytes)
{
        struct des_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
        struct blkcipher_walk walk;
        int err;
        unsigned int enc_bytes;

        DPRINTF(1, "\n");
        blkcipher_walk_init(&walk, dst, src, nbytes);
        err = blkcipher_walk_virt(desc, &walk);

        while ((nbytes = enc_bytes = walk.nbytes)) {
                u8 *iv = walk.iv;
                enc_bytes -= (nbytes % DES_BLOCK_SIZE);
                ifx_deu_des_cbc(ctx, walk.dst.virt.addr, walk.src.virt.addr, 
                               iv, enc_bytes, CRYPTO_DIR_ENCRYPT, 0);
                nbytes &= DES_BLOCK_SIZE - 1;
                err = blkcipher_walk_done(desc, &walk, nbytes);
        }

        return err;
}