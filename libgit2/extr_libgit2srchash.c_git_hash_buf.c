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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_hash_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  git_hash_ctx_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ git_hash_ctx_init (int /*<<< orphan*/ *) ; 
 int git_hash_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_hash_update (int /*<<< orphan*/ *,void const*,size_t) ; 

int git_hash_buf(git_oid *out, const void *data, size_t len)
{
	git_hash_ctx ctx;
	int error = 0;

	if (git_hash_ctx_init(&ctx) < 0)
		return -1;

	if ((error = git_hash_update(&ctx, data, len)) >= 0)
		error = git_hash_final(out, &ctx);

	git_hash_ctx_cleanup(&ctx);
	
	return error;
}