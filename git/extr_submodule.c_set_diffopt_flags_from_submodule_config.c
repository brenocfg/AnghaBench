#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct submodule {char* ignore; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int ignore_submodules; } ;
struct diff_options {TYPE_1__ flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  handle_ignore_submodules_arg (struct diff_options*,char const*) ; 
 scalar_t__ is_gitmodules_unmerged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_oid ; 
 scalar_t__ repo_config_get_string_const (TYPE_2__*,char*,char const**) ; 
 struct submodule* submodule_from_path (TYPE_2__*,int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* the_repository ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ) ; 

void set_diffopt_flags_from_submodule_config(struct diff_options *diffopt,
					     const char *path)
{
	const struct submodule *submodule = submodule_from_path(the_repository,
								&null_oid, path);
	if (submodule) {
		const char *ignore;
		char *key;

		key = xstrfmt("submodule.%s.ignore", submodule->name);
		if (repo_config_get_string_const(the_repository, key, &ignore))
			ignore = submodule->ignore;
		free(key);

		if (ignore)
			handle_ignore_submodules_arg(diffopt, ignore);
		else if (is_gitmodules_unmerged(the_repository->index))
			diffopt->flags.ignore_submodules = 1;
	}
}