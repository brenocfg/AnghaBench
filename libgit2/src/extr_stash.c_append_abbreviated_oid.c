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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_put (int /*<<< orphan*/ *,char*,int) ; 
 char* git_oid_allocfmt (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int append_abbreviated_oid(git_buf *out, const git_oid *b_commit)
{
	char *formatted_oid;

	formatted_oid = git_oid_allocfmt(b_commit);
	GIT_ERROR_CHECK_ALLOC(formatted_oid);

	git_buf_put(out, formatted_oid, 7);
	git__free(formatted_oid);

	return git_buf_oom(out) ? -1 : 0;
}