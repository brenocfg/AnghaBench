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
typedef  int u_int ;
typedef  int u_char ;
struct hmac_ctx {int /*<<< orphan*/  outerctx; int /*<<< orphan*/  innerctx; } ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  k_opad ;
typedef  int /*<<< orphan*/  k_ipad ;
typedef  int /*<<< orphan*/  SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512_Update (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  bcopy (char const*,int*,size_t) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  explicit_bzero (int*,int) ; 

void
g_eli_crypto_hmac_init(struct hmac_ctx *ctx, const char *hkey,
    size_t hkeylen)
{
	u_char k_ipad[128], k_opad[128], key[128];
	SHA512_CTX lctx;
	u_int i;

	bzero(key, sizeof(key));
	if (hkeylen == 0)
		; /* do nothing */
	else if (hkeylen <= 128)
		bcopy(hkey, key, hkeylen);
	else {
		/* If key is longer than 128 bytes reset it to key = SHA512(key). */
		SHA512_Init(&lctx);
		SHA512_Update(&lctx, hkey, hkeylen);
		SHA512_Final(key, &lctx);
	}

	/* XOR key with ipad and opad values. */
	for (i = 0; i < sizeof(key); i++) {
		k_ipad[i] = key[i] ^ 0x36;
		k_opad[i] = key[i] ^ 0x5c;
	}
	explicit_bzero(key, sizeof(key));
	/* Start inner SHA512. */
	SHA512_Init(&ctx->innerctx);
	SHA512_Update(&ctx->innerctx, k_ipad, sizeof(k_ipad));
	explicit_bzero(k_ipad, sizeof(k_ipad));
	/* Start outer SHA512. */
	SHA512_Init(&ctx->outerctx);
	SHA512_Update(&ctx->outerctx, k_opad, sizeof(k_opad));
	explicit_bzero(k_opad, sizeof(k_opad));
}