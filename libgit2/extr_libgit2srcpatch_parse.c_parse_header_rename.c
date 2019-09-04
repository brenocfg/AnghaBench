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
 int /*<<< orphan*/  header_path_len (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_header_path_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_header_rename(
	char **out,
	git_patch_parse_ctx *ctx)
{
	git_buf path = GIT_BUF_INIT;

	if (parse_header_path_buf(&path, ctx, header_path_len(ctx)) < 0)
		return -1;

	/* Note: the `rename from` and `rename to` lines include the literal
	 * filename.  They do *not* include the prefix.  (Who needs consistency?)
	 */
	*out = git_buf_detach(&path);
	return 0;
}