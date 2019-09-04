#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
struct repository {int /*<<< orphan*/  commondir; scalar_t__ different_commondir; TYPE_2__* objects; int /*<<< orphan*/  index_file; int /*<<< orphan*/  graft_file; } ;
struct TYPE_4__ {TYPE_1__* odb; } ;
struct TYPE_3__ {scalar_t__ path; } ;

/* Variables and functions */
 scalar_t__ dir_prefix (char const*,char*) ; 
 scalar_t__ git_hooks_path ; 
 scalar_t__ is_dir_file (char const*,char*,char*) ; 
 int /*<<< orphan*/  replace_dir (struct strbuf*,int,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_common_dir (struct strbuf*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adjust_git_path(const struct repository *repo,
			    struct strbuf *buf, int git_dir_len)
{
	const char *base = buf->buf + git_dir_len;
	if (is_dir_file(base, "info", "grafts"))
		strbuf_splice(buf, 0, buf->len,
			      repo->graft_file, strlen(repo->graft_file));
	else if (!strcmp(base, "index"))
		strbuf_splice(buf, 0, buf->len,
			      repo->index_file, strlen(repo->index_file));
	else if (dir_prefix(base, "objects"))
		replace_dir(buf, git_dir_len + 7, repo->objects->odb->path);
	else if (git_hooks_path && dir_prefix(base, "hooks"))
		replace_dir(buf, git_dir_len + 5, git_hooks_path);
	else if (repo->different_commondir)
		update_common_dir(buf, git_dir_len, repo->commondir);
}