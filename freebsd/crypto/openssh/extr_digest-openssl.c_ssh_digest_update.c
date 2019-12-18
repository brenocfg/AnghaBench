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
struct ssh_digest_ctx {int /*<<< orphan*/  mdctx; } ;

/* Variables and functions */
 int EVP_DigestUpdate (int /*<<< orphan*/ ,void const*,size_t) ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 

int
ssh_digest_update(struct ssh_digest_ctx *ctx, const void *m, size_t mlen)
{
	if (EVP_DigestUpdate(ctx->mdctx, m, mlen) != 1)
		return SSH_ERR_LIBCRYPTO_ERROR;
	return 0;
}