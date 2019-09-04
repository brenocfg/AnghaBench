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
struct object_id {int dummy; } ;
struct TYPE_2__ {int has_changes; scalar_t__ quick; scalar_t__ diff_from_contents; scalar_t__ reverse_diff; } ;
struct diff_options {TYPE_1__ flags; int /*<<< orphan*/  repo; scalar_t__ skip_stat_unmatch; int /*<<< orphan*/  prefix_length; scalar_t__ prefix; } ;
struct diff_filespec {unsigned int dirty_submodule; } ;
struct diff_filepair {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP (unsigned int,unsigned int) ; 
 scalar_t__ S_ISGITLINK (unsigned int) ; 
 struct diff_filespec* alloc_filespec (char const*) ; 
 int /*<<< orphan*/  diff_filespec_check_stat_unmatch (int /*<<< orphan*/ ,struct diff_filepair*) ; 
 struct diff_filepair* diff_queue (int /*<<< orphan*/ *,struct diff_filespec*,struct diff_filespec*) ; 
 int /*<<< orphan*/  diff_queued_diff ; 
 int /*<<< orphan*/  fill_filespec (struct diff_filespec*,struct object_id const*,int,unsigned int) ; 
 scalar_t__ is_submodule_ignored (char const*,struct diff_options*) ; 
 scalar_t__ strncmp (char const*,scalar_t__,int /*<<< orphan*/ ) ; 

void diff_change(struct diff_options *options,
		 unsigned old_mode, unsigned new_mode,
		 const struct object_id *old_oid,
		 const struct object_id *new_oid,
		 int old_oid_valid, int new_oid_valid,
		 const char *concatpath,
		 unsigned old_dirty_submodule, unsigned new_dirty_submodule)
{
	struct diff_filespec *one, *two;
	struct diff_filepair *p;

	if (S_ISGITLINK(old_mode) && S_ISGITLINK(new_mode) &&
	    is_submodule_ignored(concatpath, options))
		return;

	if (options->flags.reverse_diff) {
		SWAP(old_mode, new_mode);
		SWAP(old_oid, new_oid);
		SWAP(old_oid_valid, new_oid_valid);
		SWAP(old_dirty_submodule, new_dirty_submodule);
	}

	if (options->prefix &&
	    strncmp(concatpath, options->prefix, options->prefix_length))
		return;

	one = alloc_filespec(concatpath);
	two = alloc_filespec(concatpath);
	fill_filespec(one, old_oid, old_oid_valid, old_mode);
	fill_filespec(two, new_oid, new_oid_valid, new_mode);
	one->dirty_submodule = old_dirty_submodule;
	two->dirty_submodule = new_dirty_submodule;
	p = diff_queue(&diff_queued_diff, one, two);

	if (options->flags.diff_from_contents)
		return;

	if (options->flags.quick && options->skip_stat_unmatch &&
	    !diff_filespec_check_stat_unmatch(options->repo, p))
		return;

	options->flags.has_changes = 1;
}