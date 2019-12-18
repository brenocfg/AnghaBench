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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct pathspec {int dummy; } ;
struct index_state {int dummy; } ;
struct dir_struct {int flags; } ;

/* Variables and functions */
 int DIR_SHOW_OTHER_DIRECTORIES ; 
 int /*<<< orphan*/  DT_DIR ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  is_directory (int /*<<< orphan*/ ) ; 
 char* memchr (char const*,char,int) ; 
 scalar_t__ path_none ; 
 scalar_t__ simplify_away (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pathspec const*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ treat_one_path (struct dir_struct*,int /*<<< orphan*/ *,struct index_state*,struct strbuf*,int,struct pathspec const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int treat_leading_path(struct dir_struct *dir,
			      struct index_state *istate,
			      const char *path, int len,
			      const struct pathspec *pathspec)
{
	struct strbuf sb = STRBUF_INIT;
	int baselen, rc = 0;
	const char *cp;
	int old_flags = dir->flags;

	while (len && path[len - 1] == '/')
		len--;
	if (!len)
		return 1;
	baselen = 0;
	dir->flags &= ~DIR_SHOW_OTHER_DIRECTORIES;
	while (1) {
		cp = path + baselen + !!baselen;
		cp = memchr(cp, '/', path + len - cp);
		if (!cp)
			baselen = len;
		else
			baselen = cp - path;
		strbuf_setlen(&sb, 0);
		strbuf_add(&sb, path, baselen);
		if (!is_directory(sb.buf))
			break;
		if (simplify_away(sb.buf, sb.len, pathspec))
			break;
		if (treat_one_path(dir, NULL, istate, &sb, baselen, pathspec,
				   DT_DIR, NULL) == path_none)
			break; /* do not recurse into it */
		if (len <= baselen) {
			rc = 1;
			break; /* finished checking */
		}
	}
	strbuf_release(&sb);
	dir->flags = old_flags;
	return rc;
}