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
struct TYPE_3__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  sha1; } ;
typedef  TYPE_1__ git_hash_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HASH_ALGO_SHA1 ; 
 int git_hash_sha1_ctx_init (int /*<<< orphan*/ *) ; 

int git_hash_ctx_init(git_hash_ctx *ctx)
{
	int error;

	if ((error = git_hash_sha1_ctx_init(&ctx->sha1)) < 0)
		return error;

	ctx->algo = GIT_HASH_ALGO_SHA1;

	return 0;
}