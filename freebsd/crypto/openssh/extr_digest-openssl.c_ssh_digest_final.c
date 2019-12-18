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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ssh_digest_ctx {int /*<<< orphan*/  mdctx; int /*<<< orphan*/  alg; } ;
struct ssh_digest {size_t digest_len; } ;

/* Variables and functions */
 int EVP_DigestFinal_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 size_t UINT_MAX ; 
 struct ssh_digest* ssh_digest_by_alg (int /*<<< orphan*/ ) ; 

int
ssh_digest_final(struct ssh_digest_ctx *ctx, u_char *d, size_t dlen)
{
	const struct ssh_digest *digest = ssh_digest_by_alg(ctx->alg);
	u_int l = dlen;

	if (digest == NULL || dlen > UINT_MAX)
		return SSH_ERR_INVALID_ARGUMENT;
	if (dlen < digest->digest_len) /* No truncation allowed */
		return SSH_ERR_INVALID_ARGUMENT;
	if (EVP_DigestFinal_ex(ctx->mdctx, d, &l) != 1)
		return SSH_ERR_LIBCRYPTO_ERROR;
	if (l != digest->digest_len) /* sanity */
		return SSH_ERR_INTERNAL_ERROR;
	return 0;
}