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

/* Variables and functions */
 int /*<<< orphan*/  die_usage (int,char const**,char*) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  print_config_from_gitmodules (struct repository*,char const*) ; 
 scalar_t__ repo_submodule_init (struct repository*,int /*<<< orphan*/ ,struct submodule const*) ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 int /*<<< orphan*/  submodule_free (int /*<<< orphan*/ ) ; 
 struct submodule* submodule_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

int cmd__submodule_nested_repo_config(int argc, const char **argv)
{
	struct repository subrepo;
	const struct submodule *sub;

	if (argc < 3)
		die_usage(argc, argv, "Wrong number of arguments.");

	setup_git_directory();

	sub = submodule_from_path(the_repository, &null_oid, argv[1]);
	if (repo_submodule_init(&subrepo, the_repository, sub)) {
		die_usage(argc, argv, "Submodule not found.");
	}

	/* Read the config of _child_ submodules. */
	print_config_from_gitmodules(&subrepo, argv[2]);

	submodule_free(the_repository);

	return 0;
}