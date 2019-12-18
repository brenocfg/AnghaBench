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
struct ssh_hmac_ctx {int buf_len; struct ssh_hmac_ctx* buf; int /*<<< orphan*/  digest; int /*<<< orphan*/  octx; int /*<<< orphan*/  ictx; } ;

/* Variables and functions */
 int /*<<< orphan*/  explicit_bzero (struct ssh_hmac_ctx*,int) ; 
 int /*<<< orphan*/  free (struct ssh_hmac_ctx*) ; 
 int /*<<< orphan*/  ssh_digest_free (int /*<<< orphan*/ ) ; 

void
ssh_hmac_free(struct ssh_hmac_ctx *ctx)
{
	if (ctx != NULL) {
		ssh_digest_free(ctx->ictx);
		ssh_digest_free(ctx->octx);
		ssh_digest_free(ctx->digest);
		if (ctx->buf) {
			explicit_bzero(ctx->buf, ctx->buf_len);
			free(ctx->buf);
		}
		explicit_bzero(ctx, sizeof(*ctx));
		free(ctx);
	}
}