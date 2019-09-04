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
struct submodule {int /*<<< orphan*/  name; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_git_directory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_oid ; 
 char* read_gitfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_complete (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_git_path (struct strbuf*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 struct submodule* submodule_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

int submodule_to_gitdir(struct strbuf *buf, const char *submodule)
{
	const struct submodule *sub;
	const char *git_dir;
	int ret = 0;

	strbuf_reset(buf);
	strbuf_addstr(buf, submodule);
	strbuf_complete(buf, '/');
	strbuf_addstr(buf, ".git");

	git_dir = read_gitfile(buf->buf);
	if (git_dir) {
		strbuf_reset(buf);
		strbuf_addstr(buf, git_dir);
	}
	if (!is_git_directory(buf->buf)) {
		sub = submodule_from_path(the_repository, &null_oid, submodule);
		if (!sub) {
			ret = -1;
			goto cleanup;
		}
		strbuf_reset(buf);
		strbuf_git_path(buf, "%s/%s", "modules", sub->name);
	}

cleanup:
	return ret;
}