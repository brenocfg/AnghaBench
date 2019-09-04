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
struct submodule {int dummy; } ;
struct repository {int dummy; } ;
struct dir_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  repo_clear (struct repository*) ; 
 scalar_t__ repo_read_index (struct repository*) ; 
 scalar_t__ repo_submodule_init (struct repository*,struct repository*,struct submodule const*) ; 
 int /*<<< orphan*/  show_files (struct repository*,struct dir_struct*) ; 
 struct submodule* submodule_from_path (struct repository*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void show_submodule(struct repository *superproject,
			   struct dir_struct *dir, const char *path)
{
	struct repository subrepo;
	const struct submodule *sub = submodule_from_path(superproject,
							  &null_oid, path);

	if (repo_submodule_init(&subrepo, superproject, sub))
		return;

	if (repo_read_index(&subrepo) < 0)
		die("index file corrupt");

	show_files(&subrepo, dir);

	repo_clear(&subrepo);
}