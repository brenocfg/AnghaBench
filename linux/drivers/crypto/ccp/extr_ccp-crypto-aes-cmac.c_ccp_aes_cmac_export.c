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
struct ccp_aes_cmac_req_ctx {struct ccp_aes_cmac_exp_ctx* buf; int /*<<< orphan*/  buf_count; struct ccp_aes_cmac_exp_ctx* iv; int /*<<< orphan*/  null_msg; } ;
struct ccp_aes_cmac_exp_ctx {void* iv; void* buf; int /*<<< orphan*/  buf_count; int /*<<< orphan*/  null_msg; } ;
struct ahash_request {int dummy; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 struct ccp_aes_cmac_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (void*,struct ccp_aes_cmac_exp_ctx*,int) ; 
 int /*<<< orphan*/  memset (struct ccp_aes_cmac_exp_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccp_aes_cmac_export(struct ahash_request *req, void *out)
{
	struct ccp_aes_cmac_req_ctx *rctx = ahash_request_ctx(req);
	struct ccp_aes_cmac_exp_ctx state;

	/* Don't let anything leak to 'out' */
	memset(&state, 0, sizeof(state));

	state.null_msg = rctx->null_msg;
	memcpy(state.iv, rctx->iv, sizeof(state.iv));
	state.buf_count = rctx->buf_count;
	memcpy(state.buf, rctx->buf, sizeof(state.buf));

	/* 'out' may not be aligned so memcpy from local variable */
	memcpy(out, &state, sizeof(state));

	return 0;
}