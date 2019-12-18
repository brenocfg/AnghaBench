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
typedef  int u64 ;
struct skcipher_request {int cryptlen; struct scatterlist* dst; struct scatterlist* src; int /*<<< orphan*/  iv; } ;
struct scatterlist {int dummy; } ;
struct scatter_walk {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_kw_block {int /*<<< orphan*/  A; int /*<<< orphan*/  R; } ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int SEMIBSIZE ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  crypto_cipher_decrypt_one (struct crypto_cipher*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_kw_scatterlist_ff (struct scatter_walk*,struct scatterlist*,unsigned int) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_kw_block*,int) ; 
 int /*<<< orphan*/  scatterwalk_copychunks (int /*<<< orphan*/ *,struct scatter_walk*,int,int) ; 
 struct crypto_cipher* skcipher_cipher_simple (struct crypto_skcipher*) ; 

__attribute__((used)) static int crypto_kw_decrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct crypto_cipher *cipher = skcipher_cipher_simple(tfm);
	struct crypto_kw_block block;
	struct scatterlist *src, *dst;
	u64 t = 6 * ((req->cryptlen) >> 3);
	unsigned int i;
	int ret = 0;

	/*
	 * Require at least 2 semiblocks (note, the 3rd semiblock that is
	 * required by SP800-38F is the IV.
	 */
	if (req->cryptlen < (2 * SEMIBSIZE) || req->cryptlen % SEMIBSIZE)
		return -EINVAL;

	/* Place the IV into block A */
	memcpy(&block.A, req->iv, SEMIBSIZE);

	/*
	 * src scatterlist is read-only. dst scatterlist is r/w. During the
	 * first loop, src points to req->src and dst to req->dst. For any
	 * subsequent round, the code operates on req->dst only.
	 */
	src = req->src;
	dst = req->dst;

	for (i = 0; i < 6; i++) {
		struct scatter_walk src_walk, dst_walk;
		unsigned int nbytes = req->cryptlen;

		while (nbytes) {
			/* move pointer by nbytes in the SGL */
			crypto_kw_scatterlist_ff(&src_walk, src, nbytes);
			/* get the source block */
			scatterwalk_copychunks(&block.R, &src_walk, SEMIBSIZE,
					       false);

			/* perform KW operation: modify IV with counter */
			block.A ^= cpu_to_be64(t);
			t--;
			/* perform KW operation: decrypt block */
			crypto_cipher_decrypt_one(cipher, (u8 *)&block,
						  (u8 *)&block);

			/* move pointer by nbytes in the SGL */
			crypto_kw_scatterlist_ff(&dst_walk, dst, nbytes);
			/* Copy block->R into place */
			scatterwalk_copychunks(&block.R, &dst_walk, SEMIBSIZE,
					       true);

			nbytes -= SEMIBSIZE;
		}

		/* we now start to operate on the dst SGL only */
		src = req->dst;
		dst = req->dst;
	}

	/* Perform authentication check */
	if (block.A != cpu_to_be64(0xa6a6a6a6a6a6a6a6ULL))
		ret = -EBADMSG;

	memzero_explicit(&block, sizeof(struct crypto_kw_block));

	return ret;
}