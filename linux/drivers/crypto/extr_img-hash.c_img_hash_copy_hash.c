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
typedef  int /*<<< orphan*/  u32 ;
struct img_hash_request_ctx {int digsize; int /*<<< orphan*/  hdev; scalar_t__ digest; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct img_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  img_hash_read_result_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_hash_copy_hash(struct ahash_request *req)
{
	struct img_hash_request_ctx *ctx = ahash_request_ctx(req);
	u32 *hash = (u32 *)ctx->digest;
	int i;

	for (i = (ctx->digsize / sizeof(u32)) - 1; i >= 0; i--)
		hash[i] = img_hash_read_result_queue(ctx->hdev);
}