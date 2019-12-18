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
struct caam_hash_state {scalar_t__ buflen_1; scalar_t__ buflen_0; scalar_t__ buf_dma; scalar_t__ current_buf; scalar_t__ ctx_dma_len; scalar_t__ ctx_dma; int /*<<< orphan*/  final; int /*<<< orphan*/  finup; int /*<<< orphan*/  update; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_final_no_ctx ; 
 int /*<<< orphan*/  ahash_finup_first ; 
 struct caam_hash_state* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_update_first ; 

__attribute__((used)) static int ahash_init(struct ahash_request *req)
{
	struct caam_hash_state *state = ahash_request_ctx(req);

	state->update = ahash_update_first;
	state->finup = ahash_finup_first;
	state->final = ahash_final_no_ctx;

	state->ctx_dma = 0;
	state->ctx_dma_len = 0;
	state->current_buf = 0;
	state->buf_dma = 0;
	state->buflen_0 = 0;
	state->buflen_1 = 0;

	return 0;
}