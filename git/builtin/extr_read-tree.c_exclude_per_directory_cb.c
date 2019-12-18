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
struct unpack_trees_options {struct dir_struct* dir; } ;
struct option {scalar_t__ value; } ;
struct dir_struct {char const* exclude_per_dir; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  DIR_SHOW_IGNORED ; 
 int /*<<< orphan*/  die (char*) ; 
 struct dir_struct* xcalloc (int,int) ; 

__attribute__((used)) static int exclude_per_directory_cb(const struct option *opt, const char *arg,
				    int unset)
{
	struct dir_struct *dir;
	struct unpack_trees_options *opts;

	BUG_ON_OPT_NEG(unset);

	opts = (struct unpack_trees_options *)opt->value;

	if (opts->dir)
		die("more than one --exclude-per-directory given.");

	dir = xcalloc(1, sizeof(*opts->dir));
	dir->flags |= DIR_SHOW_IGNORED;
	dir->exclude_per_dir = arg;
	opts->dir = dir;
	/* We do not need to nor want to do read-directory
	 * here; we are merely interested in reusing the
	 * per directory ignore stack mechanism.
	 */
	return 0;
}