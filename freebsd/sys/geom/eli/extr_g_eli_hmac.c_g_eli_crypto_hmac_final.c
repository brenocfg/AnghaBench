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
typedef  int /*<<< orphan*/  uint8_t ;
struct hmac_ctx {int /*<<< orphan*/  outerctx; int /*<<< orphan*/  innerctx; } ;
typedef  struct hmac_ctx u_char ;
typedef  int /*<<< orphan*/  digest ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_Final (struct hmac_ctx*,int /*<<< orphan*/ *) ; 
 int SHA512_MDLEN ; 
 int /*<<< orphan*/  SHA512_Update (int /*<<< orphan*/ *,struct hmac_ctx*,int) ; 
 int /*<<< orphan*/  bcopy (struct hmac_ctx*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  explicit_bzero (struct hmac_ctx*,int) ; 

void
g_eli_crypto_hmac_final(struct hmac_ctx *ctx, uint8_t *md, size_t mdsize)
{
	u_char digest[SHA512_MDLEN];

	/* Complete inner hash */
	SHA512_Final(digest, &ctx->innerctx);

	/* Complete outer hash */
	SHA512_Update(&ctx->outerctx, digest, sizeof(digest));
	SHA512_Final(digest, &ctx->outerctx);

	explicit_bzero(ctx, sizeof(*ctx));
	/* mdsize == 0 means "Give me the whole hash!" */
	if (mdsize == 0)
		mdsize = SHA512_MDLEN;
	bcopy(digest, md, mdsize);
	explicit_bzero(digest, sizeof(digest));
}