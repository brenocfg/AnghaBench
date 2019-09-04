#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_6__ {TYPE_1__* items; } ;
struct rev_info {int /*<<< orphan*/  diffopt; TYPE_3__ prune_data; } ;
struct object_array_entry {char const* path; TYPE_2__* item; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {char* match; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUARD_PATHSPEC (TYPE_3__*,int) ; 
 int PATHSPEC_FROMTOP ; 
 int PATHSPEC_LITERAL ; 
 int /*<<< orphan*/  S_IFINVALID ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  builtin_diff_usage ; 
 int /*<<< orphan*/  canon_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  diff_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_set_mnemonic_prefix (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  diffcore_std (int /*<<< orphan*/ *) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  stuff_change (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int builtin_diff_b_f(struct rev_info *revs,
			    int argc, const char **argv,
			    struct object_array_entry **blob)
{
	/* Blob vs file in the working tree*/
	struct stat st;
	const char *path;

	if (argc > 1)
		usage(builtin_diff_usage);

	GUARD_PATHSPEC(&revs->prune_data, PATHSPEC_FROMTOP | PATHSPEC_LITERAL);
	path = revs->prune_data.items[0].match;

	if (lstat(path, &st))
		die_errno(_("failed to stat '%s'"), path);
	if (!(S_ISREG(st.st_mode) || S_ISLNK(st.st_mode)))
		die(_("'%s': not a regular file or symlink"), path);

	diff_set_mnemonic_prefix(&revs->diffopt, "o/", "w/");

	if (blob[0]->mode == S_IFINVALID)
		blob[0]->mode = canon_mode(st.st_mode);

	stuff_change(&revs->diffopt,
		     blob[0]->mode, canon_mode(st.st_mode),
		     &blob[0]->item->oid, &null_oid,
		     1, 0,
		     blob[0]->path ? blob[0]->path : path,
		     path);
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);
	return 0;
}