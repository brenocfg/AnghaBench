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
struct artpec6_hash_request_context {int /*<<< orphan*/  digeststate; int /*<<< orphan*/  partial_buffer; int /*<<< orphan*/  hash_md; int /*<<< orphan*/  hash_flags; int /*<<< orphan*/  partial_bytes; int /*<<< orphan*/  digcnt; } ;
struct artpec6_hash_export_state {int /*<<< orphan*/  digeststate; int /*<<< orphan*/  partial_buffer; void* oper; int /*<<< orphan*/  hash_flags; int /*<<< orphan*/  partial_bytes; int /*<<< orphan*/  digcnt; } ;
struct artpec6_crypto {int variant; } ;
struct ahash_request {int dummy; } ;
typedef  enum artpec6_crypto_variant { ____Placeholder_artpec6_crypto_variant } artpec6_crypto_variant ;

/* Variables and functions */
 int /*<<< orphan*/  A6_CRY_MD_OPER ; 
 int /*<<< orphan*/  A7_CRY_MD_OPER ; 
 int ARTPEC6_CRYPTO ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 void* FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct artpec6_hash_request_context* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  artpec6_crypto_dev ; 
 struct artpec6_crypto* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int artpec6_crypto_hash_export(struct ahash_request *req, void *out)
{
	const struct artpec6_hash_request_context *ctx = ahash_request_ctx(req);
	struct artpec6_hash_export_state *state = out;
	struct artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	enum artpec6_crypto_variant variant = ac->variant;

	BUILD_BUG_ON(sizeof(state->partial_buffer) !=
		     sizeof(ctx->partial_buffer));
	BUILD_BUG_ON(sizeof(state->digeststate) != sizeof(ctx->digeststate));

	state->digcnt = ctx->digcnt;
	state->partial_bytes = ctx->partial_bytes;
	state->hash_flags = ctx->hash_flags;

	if (variant == ARTPEC6_CRYPTO)
		state->oper = FIELD_GET(A6_CRY_MD_OPER, ctx->hash_md);
	else
		state->oper = FIELD_GET(A7_CRY_MD_OPER, ctx->hash_md);

	memcpy(state->partial_buffer, ctx->partial_buffer,
	       sizeof(state->partial_buffer));
	memcpy(state->digeststate, ctx->digeststate,
	       sizeof(state->digeststate));

	return 0;
}