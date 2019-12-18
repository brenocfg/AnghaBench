#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct index_state {int cache_nr; TYPE_1__** cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_symlink_leading_path (char const*,int /*<<< orphan*/ ) ; 
 int index_name_pos (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_empty_dir (char const*) ; 
 int /*<<< orphan*/  lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dir_in_way(struct index_state *istate, const char *path,
		      int check_working_copy, int empty_ok)
{
	int pos;
	struct strbuf dirpath = STRBUF_INIT;
	struct stat st;

	strbuf_addstr(&dirpath, path);
	strbuf_addch(&dirpath, '/');

	pos = index_name_pos(istate, dirpath.buf, dirpath.len);

	if (pos < 0)
		pos = -1 - pos;
	if (pos < istate->cache_nr &&
	    !strncmp(dirpath.buf, istate->cache[pos]->name, dirpath.len)) {
		strbuf_release(&dirpath);
		return 1;
	}

	strbuf_release(&dirpath);
	return check_working_copy && !lstat(path, &st) && S_ISDIR(st.st_mode) &&
		!(empty_ok && is_empty_dir(path)) &&
		!has_symlink_leading_path(path, strlen(path));
}