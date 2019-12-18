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
 size_t EVP_MD_CTX_block_size (int /*<<< orphan*/ ) ; 

size_t
ssh_digest_blocksize(struct ssh_digest_ctx *ctx)
{
	return EVP_MD_CTX_block_size(ctx->mdctx);
}