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
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct diff_tempfile {char* name; int /*<<< orphan*/  mode; int /*<<< orphan*/  hex; } ;
struct diff_filespec {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  path; scalar_t__ oid_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FILE_VALID (struct diff_filespec*) ; 
 scalar_t__ ENOENT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  S_IFLNK ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 struct diff_tempfile* claim_diff_tempfile () ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (char*,char const*) ; 
 scalar_t__ diff_populate_filespec (struct repository*,struct diff_filespec*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  oid_to_hex_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prep_temp_blob (int /*<<< orphan*/ ,char const*,struct diff_tempfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ reuse_worktree_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strbuf_readlink (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  xsnprintf (int /*<<< orphan*/ ,int,char*,...) ; 

__attribute__((used)) static struct diff_tempfile *prepare_temp_file(struct repository *r,
					       const char *name,
					       struct diff_filespec *one)
{
	struct diff_tempfile *temp = claim_diff_tempfile();

	if (!DIFF_FILE_VALID(one)) {
	not_a_valid_file:
		/* A '-' entry produces this for file-2, and
		 * a '+' entry produces this for file-1.
		 */
		temp->name = "/dev/null";
		xsnprintf(temp->hex, sizeof(temp->hex), ".");
		xsnprintf(temp->mode, sizeof(temp->mode), ".");
		return temp;
	}

	if (!S_ISGITLINK(one->mode) &&
	    (!one->oid_valid ||
	     reuse_worktree_file(r->index, name, &one->oid, 1))) {
		struct stat st;
		if (lstat(name, &st) < 0) {
			if (errno == ENOENT)
				goto not_a_valid_file;
			die_errno("stat(%s)", name);
		}
		if (S_ISLNK(st.st_mode)) {
			struct strbuf sb = STRBUF_INIT;
			if (strbuf_readlink(&sb, name, st.st_size) < 0)
				die_errno("readlink(%s)", name);
			prep_temp_blob(r->index, name, temp, sb.buf, sb.len,
				       (one->oid_valid ?
					&one->oid : &null_oid),
				       (one->oid_valid ?
					one->mode : S_IFLNK));
			strbuf_release(&sb);
		}
		else {
			/* we can borrow from the file in the work tree */
			temp->name = name;
			if (!one->oid_valid)
				oid_to_hex_r(temp->hex, &null_oid);
			else
				oid_to_hex_r(temp->hex, &one->oid);
			/* Even though we may sometimes borrow the
			 * contents from the work tree, we always want
			 * one->mode.  mode is trustworthy even when
			 * !(one->oid_valid), as long as
			 * DIFF_FILE_VALID(one).
			 */
			xsnprintf(temp->mode, sizeof(temp->mode), "%06o", one->mode);
		}
		return temp;
	}
	else {
		if (diff_populate_filespec(r, one, 0))
			die("cannot read data blob for %s", one->path);
		prep_temp_blob(r->index, name, temp,
			       one->data, one->size,
			       &one->oid, one->mode);
	}
	return temp;
}