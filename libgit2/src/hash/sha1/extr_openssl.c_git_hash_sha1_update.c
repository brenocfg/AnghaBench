#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ git_hash_sha1_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_SHA1 ; 
 int SHA1_Update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git_hash_sha1_update(git_hash_sha1_ctx *ctx, const void *data, size_t len)
{
	assert(ctx);

	if (SHA1_Update(&ctx->c, data, len) != 1) {
		git_error_set(GIT_ERROR_SHA1, "hash_openssl: failed to update hash");
		return -1;
	}

	return 0;
}