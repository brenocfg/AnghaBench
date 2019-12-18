#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct hmac_ctx {struct crypto_shash* hash; } ;
struct crypto_shash {int dummy; } ;
struct TYPE_7__ {struct crypto_shash* tfm; } ;

/* Variables and functions */
 char HMAC_IPAD_VALUE ; 
 char HMAC_OPAD_VALUE ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,struct crypto_shash*) ; 
 struct hmac_ctx* align_ptr (char*,int /*<<< orphan*/ ) ; 
 int crypto_shash_blocksize (struct crypto_shash*) ; 
 char* crypto_shash_ctx_aligned (struct crypto_shash*) ; 
 int crypto_shash_digest (TYPE_1__*,char const*,unsigned int,char*) ; 
 int crypto_shash_digestsize (struct crypto_shash*) ; 
 int crypto_shash_export (TYPE_1__*,char*) ; 
 scalar_t__ crypto_shash_init (TYPE_1__*) ; 
 int crypto_shash_statesize (struct crypto_shash*) ; 
 scalar_t__ crypto_shash_update (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  crypto_tfm_ctx_alignment () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* shash ; 

__attribute__((used)) static int hmac_setkey(struct crypto_shash *parent,
		       const u8 *inkey, unsigned int keylen)
{
	int bs = crypto_shash_blocksize(parent);
	int ds = crypto_shash_digestsize(parent);
	int ss = crypto_shash_statesize(parent);
	char *ipad = crypto_shash_ctx_aligned(parent);
	char *opad = ipad + ss;
	struct hmac_ctx *ctx = align_ptr(opad + ss,
					 crypto_tfm_ctx_alignment());
	struct crypto_shash *hash = ctx->hash;
	SHASH_DESC_ON_STACK(shash, hash);
	unsigned int i;

	shash->tfm = hash;

	if (keylen > bs) {
		int err;

		err = crypto_shash_digest(shash, inkey, keylen, ipad);
		if (err)
			return err;

		keylen = ds;
	} else
		memcpy(ipad, inkey, keylen);

	memset(ipad + keylen, 0, bs - keylen);
	memcpy(opad, ipad, bs);

	for (i = 0; i < bs; i++) {
		ipad[i] ^= HMAC_IPAD_VALUE;
		opad[i] ^= HMAC_OPAD_VALUE;
	}

	return crypto_shash_init(shash) ?:
	       crypto_shash_update(shash, ipad, bs) ?:
	       crypto_shash_export(shash, ipad) ?:
	       crypto_shash_init(shash) ?:
	       crypto_shash_update(shash, opad, bs) ?:
	       crypto_shash_export(shash, opad);
}