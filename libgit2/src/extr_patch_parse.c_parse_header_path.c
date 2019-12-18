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
typedef  int /*<<< orphan*/  git_patch_parse_ctx ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  header_path_len (int /*<<< orphan*/ *) ; 
 int parse_header_path_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_header_path(char **out, git_patch_parse_ctx *ctx)
{
	git_buf path = GIT_BUF_INIT;
	int error;

	if ((error = parse_header_path_buf(&path, ctx, header_path_len(ctx))) < 0)
		goto out;
	*out = git_buf_detach(&path);

out:
	git_buf_dispose(&path);
	return error;
}