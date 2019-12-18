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
struct TYPE_2__ {int /*<<< orphan*/  hmac; int /*<<< orphan*/  md; } ;
struct crypto_hash {int alg; TYPE_1__ u; scalar_t__ error; } ;

/* Variables and functions */
#define  CRYPTO_HASH_ALG_HMAC_MD5 131 
#define  CRYPTO_HASH_ALG_HMAC_SHA1 130 
#define  CRYPTO_HASH_ALG_MD5 129 
#define  CRYPTO_HASH_ALG_SHA1 128 
 int /*<<< orphan*/  CRYPT_OK ; 
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  hmac_done (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  md5_done (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct crypto_hash*) ; 
 int /*<<< orphan*/  sha1_done (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int crypto_hash_finish(struct crypto_hash *ctx, u8 *mac, size_t *len)
{
	int ret = 0;
	unsigned long clen;

	if (ctx == NULL)
		return -2;

	if (mac == NULL || len == NULL) {
		os_free(ctx);
		return 0;
	}

	if (ctx->error) {
		os_free(ctx);
		return -2;
	}

	switch (ctx->alg) {
	case CRYPTO_HASH_ALG_MD5:
		if (*len < 16) {
			*len = 16;
			os_free(ctx);
			return -1;
		}
		*len = 16;
		if (md5_done(&ctx->u.md, mac) != CRYPT_OK)
			ret = -2;
		break;
	case CRYPTO_HASH_ALG_SHA1:
		if (*len < 20) {
			*len = 20;
			os_free(ctx);
			return -1;
		}
		*len = 20;
		if (sha1_done(&ctx->u.md, mac) != CRYPT_OK)
			ret = -2;
		break;
	case CRYPTO_HASH_ALG_HMAC_SHA1:
		if (*len < 20) {
			*len = 20;
			os_free(ctx);
			return -1;
		}
		/* continue */
	case CRYPTO_HASH_ALG_HMAC_MD5:
		if (*len < 16) {
			*len = 16;
			os_free(ctx);
			return -1;
		}
		clen = *len;
		if (hmac_done(&ctx->u.hmac, mac, &clen) != CRYPT_OK) {
			os_free(ctx);
			return -1;
		}
		*len = clen;
		break;
	default:
		ret = -2;
		break;
	}

	os_free(ctx);

	if (TEST_FAIL())
		return -1;

	return ret;
}