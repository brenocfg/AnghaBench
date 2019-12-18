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
typedef  int /*<<< orphan*/  u_char ;
struct ssh_hmac_ctx {int /*<<< orphan*/  digest; int /*<<< orphan*/ * buf; int /*<<< orphan*/  octx; int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 size_t ssh_digest_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ ssh_digest_copy_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ssh_digest_final (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ssh_digest_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

int
ssh_hmac_final(struct ssh_hmac_ctx *ctx, u_char *d, size_t dlen)
{
	size_t len;

	len = ssh_digest_bytes(ctx->alg);
	if (dlen < len ||
	    ssh_digest_final(ctx->digest, ctx->buf, len))
		return -1;
	/* switch to octx */
	if (ssh_digest_copy_state(ctx->octx, ctx->digest) < 0 ||
	    ssh_digest_update(ctx->digest, ctx->buf, len) < 0 ||
	    ssh_digest_final(ctx->digest, d, dlen) < 0)
		return -1;
	return 0;
}