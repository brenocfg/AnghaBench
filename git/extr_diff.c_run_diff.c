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
struct strbuf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  allow_external; } ;
struct diff_options {TYPE_2__* repo; TYPE_1__ flags; scalar_t__ prefix_length; } ;
struct diff_filespec {char* path; int mode; } ;
struct diff_filepair {struct diff_filespec* two; struct diff_filespec* one; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ DIFF_FILE_VALID (struct diff_filespec*) ; 
 scalar_t__ DIFF_PAIR_UNMERGED (struct diff_filepair*) ; 
 int S_IFMT ; 
 struct diff_filespec* alloc_filespec (char*) ; 
 int /*<<< orphan*/  diff_fill_oid_info (struct diff_filespec*,int /*<<< orphan*/ ) ; 
 char* external_diff () ; 
 int /*<<< orphan*/  free (struct diff_filespec*) ; 
 int /*<<< orphan*/  run_diff_cmd (char const*,char const*,char const*,char const*,struct diff_filespec*,struct diff_filespec*,struct strbuf*,struct diff_options*,struct diff_filepair*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strip_prefix (scalar_t__,char const**,char const**) ; 

__attribute__((used)) static void run_diff(struct diff_filepair *p, struct diff_options *o)
{
	const char *pgm = external_diff();
	struct strbuf msg;
	struct diff_filespec *one = p->one;
	struct diff_filespec *two = p->two;
	const char *name;
	const char *other;
	const char *attr_path;

	name  = one->path;
	other = (strcmp(name, two->path) ? two->path : NULL);
	attr_path = name;
	if (o->prefix_length)
		strip_prefix(o->prefix_length, &name, &other);

	if (!o->flags.allow_external)
		pgm = NULL;

	if (DIFF_PAIR_UNMERGED(p)) {
		run_diff_cmd(pgm, name, NULL, attr_path,
			     NULL, NULL, NULL, o, p);
		return;
	}

	diff_fill_oid_info(one, o->repo->index);
	diff_fill_oid_info(two, o->repo->index);

	if (!pgm &&
	    DIFF_FILE_VALID(one) && DIFF_FILE_VALID(two) &&
	    (S_IFMT & one->mode) != (S_IFMT & two->mode)) {
		/*
		 * a filepair that changes between file and symlink
		 * needs to be split into deletion and creation.
		 */
		struct diff_filespec *null = alloc_filespec(two->path);
		run_diff_cmd(NULL, name, other, attr_path,
			     one, null, &msg,
			     o, p);
		free(null);
		strbuf_release(&msg);

		null = alloc_filespec(one->path);
		run_diff_cmd(NULL, name, other, attr_path,
			     null, two, &msg, o, p);
		free(null);
	}
	else
		run_diff_cmd(pgm, name, other, attr_path,
			     one, two, &msg, o, p);

	strbuf_release(&msg);
}