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
struct sha256_state {int /*<<< orphan*/  buf; int /*<<< orphan*/  state; int /*<<< orphan*/  count; } ;
struct sha1_state {int /*<<< orphan*/  buffer; int /*<<< orphan*/  state; int /*<<< orphan*/  count; } ;
struct qce_sha_reqctx {unsigned long flags; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_SHA1 (unsigned long) ; 
 scalar_t__ IS_SHA1_HMAC (unsigned long) ; 
 scalar_t__ IS_SHA256 (unsigned long) ; 
 scalar_t__ IS_SHA256_HMAC (unsigned long) ; 
 int IS_SHA_HMAC (unsigned long) ; 
 struct qce_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int qce_import_common (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qce_ahash_import(struct ahash_request *req, const void *in)
{
	struct qce_sha_reqctx *rctx = ahash_request_ctx(req);
	unsigned long flags = rctx->flags;
	bool hmac = IS_SHA_HMAC(flags);
	int ret = -EINVAL;

	if (IS_SHA1(flags) || IS_SHA1_HMAC(flags)) {
		const struct sha1_state *state = in;

		ret = qce_import_common(req, state->count, state->state,
					state->buffer, hmac);
	} else if (IS_SHA256(flags) || IS_SHA256_HMAC(flags)) {
		const struct sha256_state *state = in;

		ret = qce_import_common(req, state->count, state->state,
					state->buf, hmac);
	}

	return ret;
}