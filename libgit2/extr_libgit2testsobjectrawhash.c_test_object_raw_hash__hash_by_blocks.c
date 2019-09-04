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
 int /*<<< orphan*/  bye_id ; 
 int /*<<< orphan*/  bye_text ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_hash_ctx_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hello_id ; 
 int /*<<< orphan*/  hello_text ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_object_raw_hash__hash_by_blocks(void)
{
	git_hash_ctx ctx;
	git_oid id1, id2;

	cl_git_pass(git_hash_ctx_init(&ctx));

	/* should already be init'd */
	cl_git_pass(git_hash_update(&ctx, hello_text, strlen(hello_text)));
	cl_git_pass(git_hash_final(&id2, &ctx));
	cl_git_pass(git_oid_fromstr(&id1, hello_id));
	cl_assert(git_oid_cmp(&id1, &id2) == 0);

	/* reinit should permit reuse */
	cl_git_pass(git_hash_init(&ctx));
	cl_git_pass(git_hash_update(&ctx, bye_text, strlen(bye_text)));
	cl_git_pass(git_hash_final(&id2, &ctx));
	cl_git_pass(git_oid_fromstr(&id1, bye_id));
	cl_assert(git_oid_cmp(&id1, &id2) == 0);

	git_hash_ctx_cleanup(&ctx);
}