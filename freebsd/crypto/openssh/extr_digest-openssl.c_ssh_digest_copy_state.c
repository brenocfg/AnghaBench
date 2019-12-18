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
struct ssh_digest_ctx {scalar_t__ alg; int /*<<< orphan*/  mdctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_copy_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 

int
ssh_digest_copy_state(struct ssh_digest_ctx *from, struct ssh_digest_ctx *to)
{
	if (from->alg != to->alg)
		return SSH_ERR_INVALID_ARGUMENT;
	/* we have bcopy-style order while openssl has memcpy-style */
	if (!EVP_MD_CTX_copy_ex(to->mdctx, from->mdctx))
		return SSH_ERR_LIBCRYPTO_ERROR;
	return 0;
}