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
struct stm32_hash_request_ctx {int /*<<< orphan*/  flags; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FLAGS_FINUP ; 
 int /*<<< orphan*/  HASH_OP_FINAL ; 
 struct stm32_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int stm32_hash_enqueue (struct ahash_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_hash_final(struct ahash_request *req)
{
	struct stm32_hash_request_ctx *rctx = ahash_request_ctx(req);

	rctx->flags |= HASH_FLAGS_FINUP;

	return stm32_hash_enqueue(req, HASH_OP_FINAL);
}