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
struct ccp_sha_req_ctx {struct ccp_sha_exp_ctx* buf; int /*<<< orphan*/  buf_count; struct ccp_sha_exp_ctx* ctx; int /*<<< orphan*/  first; int /*<<< orphan*/  msg_bits; int /*<<< orphan*/  type; } ;
struct ccp_sha_exp_ctx {void const* ctx; void const* buf; int /*<<< orphan*/  buf_count; int /*<<< orphan*/  first; int /*<<< orphan*/  msg_bits; int /*<<< orphan*/  type; } ;
struct ahash_request {int dummy; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 struct ccp_sha_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (struct ccp_sha_exp_ctx*,void const*,int) ; 
 int /*<<< orphan*/  memset (struct ccp_sha_req_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccp_sha_import(struct ahash_request *req, const void *in)
{
	struct ccp_sha_req_ctx *rctx = ahash_request_ctx(req);
	struct ccp_sha_exp_ctx state;

	/* 'in' may not be aligned so memcpy to local variable */
	memcpy(&state, in, sizeof(state));

	memset(rctx, 0, sizeof(*rctx));
	rctx->type = state.type;
	rctx->msg_bits = state.msg_bits;
	rctx->first = state.first;
	memcpy(rctx->ctx, state.ctx, sizeof(rctx->ctx));
	rctx->buf_count = state.buf_count;
	memcpy(rctx->buf, state.buf, sizeof(rctx->buf));

	return 0;
}