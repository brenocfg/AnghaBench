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
struct strbuf {int len; scalar_t__ buf; } ;
struct config_options {char* git_dir; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int WM_CASEFOLD ; 
 int WM_PATHNAME ; 
 int prepare_include_condition_pattern (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_add_absolute_path (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_realpath (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 scalar_t__ strncasecmp (scalar_t__,scalar_t__,int) ; 
 scalar_t__ strncmp (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  wildmatch (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int include_by_gitdir(const struct config_options *opts,
			     const char *cond, size_t cond_len, int icase)
{
	struct strbuf text = STRBUF_INIT;
	struct strbuf pattern = STRBUF_INIT;
	int ret = 0, prefix;
	const char *git_dir;
	int already_tried_absolute = 0;

	if (opts->git_dir)
		git_dir = opts->git_dir;
	else
		goto done;

	strbuf_realpath(&text, git_dir, 1);
	strbuf_add(&pattern, cond, cond_len);
	prefix = prepare_include_condition_pattern(&pattern);

again:
	if (prefix < 0)
		goto done;

	if (prefix > 0) {
		/*
		 * perform literal matching on the prefix part so that
		 * any wildcard character in it can't create side effects.
		 */
		if (text.len < prefix)
			goto done;
		if (!icase && strncmp(pattern.buf, text.buf, prefix))
			goto done;
		if (icase && strncasecmp(pattern.buf, text.buf, prefix))
			goto done;
	}

	ret = !wildmatch(pattern.buf + prefix, text.buf + prefix,
			 WM_PATHNAME | (icase ? WM_CASEFOLD : 0));

	if (!ret && !already_tried_absolute) {
		/*
		 * We've tried e.g. matching gitdir:~/work, but if
		 * ~/work is a symlink to /mnt/storage/work
		 * strbuf_realpath() will expand it, so the rule won't
		 * match. Let's match against a
		 * strbuf_add_absolute_path() version of the path,
		 * which'll do the right thing
		 */
		strbuf_reset(&text);
		strbuf_add_absolute_path(&text, git_dir);
		already_tried_absolute = 1;
		goto again;
	}
done:
	strbuf_release(&pattern);
	strbuf_release(&text);
	return ret;
}