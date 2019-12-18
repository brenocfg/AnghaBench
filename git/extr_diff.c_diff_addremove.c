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
struct TYPE_2__ {int has_changes; int /*<<< orphan*/  diff_from_contents; scalar_t__ reverse_diff; } ;
struct diff_options {TYPE_1__ flags; int /*<<< orphan*/  prefix_length; scalar_t__ prefix; } ;
struct diff_filespec {unsigned int dirty_submodule; } ;

/* Variables and functions */
 scalar_t__ S_ISGITLINK (unsigned int) ; 
 struct diff_filespec* alloc_filespec (char const*) ; 
 int /*<<< orphan*/  diff_queue (int /*<<< orphan*/ *,struct diff_filespec*,struct diff_filespec*) ; 
 int /*<<< orphan*/  diff_queued_diff ; 
 int /*<<< orphan*/  fill_filespec (struct diff_filespec*,struct object_id const*,int,unsigned int) ; 
 scalar_t__ is_submodule_ignored (char const*,struct diff_options*) ; 
 scalar_t__ strncmp (char const*,scalar_t__,int /*<<< orphan*/ ) ; 

void diff_addremove(struct diff_options *options,
		    int addremove, unsigned mode,
		    const struct object_id *oid,
		    int oid_valid,
		    const char *concatpath, unsigned dirty_submodule)
{
	struct diff_filespec *one, *two;

	if (S_ISGITLINK(mode) && is_submodule_ignored(concatpath, options))
		return;

	/* This may look odd, but it is a preparation for
	 * feeding "there are unchanged files which should
	 * not produce diffs, but when you are doing copy
	 * detection you would need them, so here they are"
	 * entries to the diff-core.  They will be prefixed
	 * with something like '=' or '*' (I haven't decided
	 * which but should not make any difference).
	 * Feeding the same new and old to diff_change()
	 * also has the same effect.
	 * Before the final output happens, they are pruned after
	 * merged into rename/copy pairs as appropriate.
	 */
	if (options->flags.reverse_diff)
		addremove = (addremove == '+' ? '-' :
			     addremove == '-' ? '+' : addremove);

	if (options->prefix &&
	    strncmp(concatpath, options->prefix, options->prefix_length))
		return;

	one = alloc_filespec(concatpath);
	two = alloc_filespec(concatpath);

	if (addremove != '+')
		fill_filespec(one, oid, oid_valid, mode);
	if (addremove != '-') {
		fill_filespec(two, oid, oid_valid, mode);
		two->dirty_submodule = dirty_submodule;
	}

	diff_queue(&diff_queued_diff, one, two);
	if (!options->flags.diff_from_contents)
		options->flags.has_changes = 1;
}