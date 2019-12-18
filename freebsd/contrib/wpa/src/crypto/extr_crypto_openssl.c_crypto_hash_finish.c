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
struct crypto_hash {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ ) ; 
 int HMAC_Final (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  bin_clear_free (struct crypto_hash*,int) ; 

int crypto_hash_finish(struct crypto_hash *ctx, u8 *mac, size_t *len)
{
	unsigned int mdlen;
	int res;

	if (ctx == NULL)
		return -2;

	if (mac == NULL || len == NULL) {
		HMAC_CTX_free(ctx->ctx);
		bin_clear_free(ctx, sizeof(*ctx));
		return 0;
	}

	mdlen = *len;
	res = HMAC_Final(ctx->ctx, mac, &mdlen);
	HMAC_CTX_free(ctx->ctx);
	bin_clear_free(ctx, sizeof(*ctx));

	if (TEST_FAIL())
		return -1;

	if (res == 1) {
		*len = mdlen;
		return 0;
	}

	return -1;
}