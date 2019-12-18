#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int algo; int /*<<< orphan*/  sha1; } ;
typedef  TYPE_1__ git_hash_ctx ;

/* Variables and functions */
#define  GIT_HASH_ALGO_SHA1 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_hash_sha1_ctx_cleanup (int /*<<< orphan*/ *) ; 

void git_hash_ctx_cleanup(git_hash_ctx *ctx)
{
	switch (ctx->algo) {
		case GIT_HASH_ALGO_SHA1:
			git_hash_sha1_ctx_cleanup(&ctx->sha1);
			return;
		default:
			assert(0);
	}
}