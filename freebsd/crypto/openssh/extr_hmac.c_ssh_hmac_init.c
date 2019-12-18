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
struct ssh_hmac_ctx {size_t buf_len; int* buf; int /*<<< orphan*/  digest; int /*<<< orphan*/  ictx; int /*<<< orphan*/  octx; int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  explicit_bzero (int*,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,void const*,size_t) ; 
 scalar_t__ ssh_digest_copy_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ssh_digest_memory (int /*<<< orphan*/ ,void const*,size_t,int*,size_t) ; 
 scalar_t__ ssh_digest_update (int /*<<< orphan*/ ,int*,size_t) ; 

int
ssh_hmac_init(struct ssh_hmac_ctx *ctx, const void *key, size_t klen)
{
	size_t i;

	/* reset ictx and octx if no is key given */
	if (key != NULL) {
		/* truncate long keys */
		if (klen <= ctx->buf_len)
			memcpy(ctx->buf, key, klen);
		else if (ssh_digest_memory(ctx->alg, key, klen, ctx->buf,
		    ctx->buf_len) < 0)
			return -1;
		for (i = 0; i < ctx->buf_len; i++)
			ctx->buf[i] ^= 0x36;
		if (ssh_digest_update(ctx->ictx, ctx->buf, ctx->buf_len) < 0)
			return -1;
		for (i = 0; i < ctx->buf_len; i++)
			ctx->buf[i] ^= 0x36 ^ 0x5c;
		if (ssh_digest_update(ctx->octx, ctx->buf, ctx->buf_len) < 0)
			return -1;
		explicit_bzero(ctx->buf, ctx->buf_len);
	}
	/* start with ictx */
	if (ssh_digest_copy_state(ctx->ictx, ctx->digest) < 0)
		return -1;
	return 0;
}