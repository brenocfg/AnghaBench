#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct vmac_tfm_ctx {int /*<<< orphan*/  cipher; } ;
struct TYPE_2__ {int* bytes; int /*<<< orphan*/ * pads; } ;
struct vmac_desc_ctx {int nonce_size; TYPE_1__ nonce; } ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int VMAC_NONCEBYTES ; 
 int VMAC_TAG_LEN ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (int /*<<< orphan*/ ,int*,int*) ; 
 struct vmac_tfm_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_be64 (scalar_t__,int /*<<< orphan*/ *) ; 
 struct vmac_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 
 scalar_t__ vhash_final (struct vmac_tfm_ctx const*,struct vmac_desc_ctx*) ; 

__attribute__((used)) static int vmac_final(struct shash_desc *desc, u8 *out)
{
	const struct vmac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	struct vmac_desc_ctx *dctx = shash_desc_ctx(desc);
	int index;
	u64 hash, pad;

	if (dctx->nonce_size != VMAC_NONCEBYTES)
		return -EINVAL;

	/*
	 * The VMAC specification requires a nonce at least 1 bit shorter than
	 * the block cipher's block length, so we actually only accept a 127-bit
	 * nonce.  We define the unused bit to be the first one and require that
	 * it be 0, so the needed prepending of a 0 bit is implicit.
	 */
	if (dctx->nonce.bytes[0] & 0x80)
		return -EINVAL;

	/* Finish calculating the VHASH of the message */
	hash = vhash_final(tctx, dctx);

	/* Generate pseudorandom pad by encrypting the nonce */
	BUILD_BUG_ON(VMAC_NONCEBYTES != 2 * (VMAC_TAG_LEN / 8));
	index = dctx->nonce.bytes[VMAC_NONCEBYTES - 1] & 1;
	dctx->nonce.bytes[VMAC_NONCEBYTES - 1] &= ~1;
	crypto_cipher_encrypt_one(tctx->cipher, dctx->nonce.bytes,
				  dctx->nonce.bytes);
	pad = be64_to_cpu(dctx->nonce.pads[index]);

	/* The VMAC is the sum of VHASH and the pseudorandom pad */
	put_unaligned_be64(hash + pad, out);
	return 0;
}