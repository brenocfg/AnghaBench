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
struct s5p_hash_reqctx {scalar_t__ bufcnt; scalar_t__ buffer; } ;
struct ahash_request {scalar_t__ nbytes; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ BUFLEN ; 
 struct s5p_hash_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int s5p_hash_enqueue (struct ahash_request*,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_hash_update(struct ahash_request *req)
{
	struct s5p_hash_reqctx *ctx = ahash_request_ctx(req);

	if (!req->nbytes)
		return 0;

	if (ctx->bufcnt + req->nbytes <= BUFLEN) {
		scatterwalk_map_and_copy(ctx->buffer + ctx->bufcnt, req->src,
					 0, req->nbytes, 0);
		ctx->bufcnt += req->nbytes;
		return 0;
	}

	return s5p_hash_enqueue(req, true); /* HASH_OP_UPDATE */
}