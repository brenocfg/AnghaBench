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
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; TYPE_4__ src; TYPE_2__ dst; int /*<<< orphan*/  iv; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;
struct aes_ctx {int /*<<< orphan*/  nonce; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  CRYPTO_DIR_DECRYPT ; 
 int /*<<< orphan*/  CRYPTO_DIR_ENCRYPT ; 
 int CTR_RFC3686_IV_SIZE ; 
 int CTR_RFC3686_NONCE_SIZE ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct aes_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifx_deu_aes_ctr (struct aes_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int ctr_rfc3686_aes_decrypt(struct blkcipher_desc *desc,
               struct scatterlist *dst, struct scatterlist *src,
               unsigned int nbytes)
{
    struct aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
    struct blkcipher_walk walk;
    int err, bsize = nbytes;
    u8 rfc3686_iv[16];

    blkcipher_walk_init(&walk, dst, src, nbytes);
    err = blkcipher_walk_virt(desc, &walk);

    /* set up counter block */
    memcpy(rfc3686_iv, ctx->nonce, CTR_RFC3686_NONCE_SIZE); 
    memcpy(rfc3686_iv + CTR_RFC3686_NONCE_SIZE, walk.iv, CTR_RFC3686_IV_SIZE);

    /* initialize counter portion of counter block */
    *(__be32 *)(rfc3686_iv + CTR_RFC3686_NONCE_SIZE + CTR_RFC3686_IV_SIZE) =
        cpu_to_be32(1);

    /* scatterlist source is the same size as request size, just process once */
    if (nbytes == walk.nbytes) {
	ifx_deu_aes_ctr(ctx, walk.dst.virt.addr, walk.src.virt.addr,
			rfc3686_iv, nbytes, CRYPTO_DIR_ENCRYPT, 0);
	nbytes -= walk.nbytes;
	err = blkcipher_walk_done(desc, &walk, nbytes);
	return err;
    }

    while ((nbytes = walk.nbytes) % (walk.nbytes >= AES_BLOCK_SIZE)) {
	ifx_deu_aes_ctr(ctx, walk.dst.virt.addr, walk.src.virt.addr,
			rfc3686_iv, nbytes, CRYPTO_DIR_DECRYPT, 0);

	nbytes -= walk.nbytes;
	bsize -= walk.nbytes;
	err = blkcipher_walk_done(desc, &walk, nbytes);
    }

    /* to handle remaining bytes < AES_BLOCK_SIZE */
    if (walk.nbytes) {
	ifx_deu_aes_ctr(ctx, walk.dst.virt.addr, walk.src.virt.addr,
			rfc3686_iv, walk.nbytes, CRYPTO_DIR_ENCRYPT, 0);
	err = blkcipher_walk_done(desc, &walk, 0);
    }

    return err;
}