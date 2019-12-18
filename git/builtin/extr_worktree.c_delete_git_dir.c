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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 scalar_t__ ENOTDIR ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_common_path (char*,char const*) ; 
 int remove_dir_recursively (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int delete_git_dir(const char *id)
{
	struct strbuf sb = STRBUF_INIT;
	int ret;

	strbuf_addstr(&sb, git_common_path("worktrees/%s", id));
	ret = remove_dir_recursively(&sb, 0);
	if (ret < 0 && errno == ENOTDIR)
		ret = unlink(sb.buf);
	if (ret)
		error_errno(_("failed to delete '%s'"), sb.buf);
	strbuf_release(&sb);
	return ret;
}