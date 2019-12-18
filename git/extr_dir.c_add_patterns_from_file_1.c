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
struct pattern_list {int dummy; } ;
struct oid_stat {int dummy; } ;
struct dir_struct {int /*<<< orphan*/  unmanaged_exclude_files; int /*<<< orphan*/  untracked; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXC_FILE ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct pattern_list* add_pattern_list (struct dir_struct*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ add_patterns (char const*,char*,int /*<<< orphan*/ ,struct pattern_list*,int /*<<< orphan*/ *,struct oid_stat*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void add_patterns_from_file_1(struct dir_struct *dir, const char *fname,
				     struct oid_stat *oid_stat)
{
	struct pattern_list *pl;
	/*
	 * catch setup_standard_excludes() that's called before
	 * dir->untracked is assigned. That function behaves
	 * differently when dir->untracked is non-NULL.
	 */
	if (!dir->untracked)
		dir->unmanaged_exclude_files++;
	pl = add_pattern_list(dir, EXC_FILE, fname);
	if (add_patterns(fname, "", 0, pl, NULL, oid_stat) < 0)
		die(_("cannot use %s as an exclude file"), fname);
}