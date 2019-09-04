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
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_remote_head ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_is_valid_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int create_deletion_refspecs(git_vector *out, const git_remote_head **heads, size_t heads_len)
{
	git_buf del_spec = GIT_BUF_INIT;
	size_t i;

	for (i = 0; i < heads_len; i++) {
		const git_remote_head *head = heads[i];
		/* Ignore malformed ref names (which also saves us from tag^{} */
		if (!git_reference_is_valid_name(head->name))
			return 0;

		/* Create a refspec that deletes a branch in the remote */
		if (strcmp(head->name, "refs/heads/master")) {
			cl_git_pass(git_buf_putc(&del_spec, ':'));
			cl_git_pass(git_buf_puts(&del_spec, head->name));
			cl_git_pass(git_vector_insert(out, git_buf_detach(&del_spec)));
		}
	}

	return 0;
}