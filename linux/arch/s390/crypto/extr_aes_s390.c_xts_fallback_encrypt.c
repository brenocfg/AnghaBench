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
struct scatterlist {int dummy; } ;
struct s390_xts_ctx {int /*<<< orphan*/  fallback; } ;
struct crypto_blkcipher {int dummy; } ;
struct blkcipher_desc {int /*<<< orphan*/  info; int /*<<< orphan*/  flags; struct crypto_blkcipher* tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s390_xts_ctx* crypto_blkcipher_ctx (struct crypto_blkcipher*) ; 
 unsigned int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xts_fallback_encrypt(struct blkcipher_desc *desc,
		struct scatterlist *dst, struct scatterlist *src,
		unsigned int nbytes)
{
	struct crypto_blkcipher *tfm = desc->tfm;
	struct s390_xts_ctx *xts_ctx = crypto_blkcipher_ctx(tfm);
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, xts_ctx->fallback);
	unsigned int ret;

	skcipher_request_set_sync_tfm(req, xts_ctx->fallback);
	skcipher_request_set_callback(req, desc->flags, NULL, NULL);
	skcipher_request_set_crypt(req, src, dst, nbytes, desc->info);

	ret = crypto_skcipher_encrypt(req);

	skcipher_request_zero(req);
	return ret;
}