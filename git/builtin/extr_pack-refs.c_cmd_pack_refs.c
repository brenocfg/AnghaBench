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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BIT (int /*<<< orphan*/ ,char*,unsigned int*,int /*<<< orphan*/ ,unsigned int) ; 
 struct option OPT_END () ; 
 unsigned int PACK_REFS_ALL ; 
 unsigned int PACK_REFS_PRUNE ; 
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  pack_refs_usage ; 
 scalar_t__ parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int refs_pack_refs (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

int cmd_pack_refs(int argc, const char **argv, const char *prefix)
{
	unsigned int flags = PACK_REFS_PRUNE;
	struct option opts[] = {
		OPT_BIT(0, "all",   &flags, N_("pack everything"), PACK_REFS_ALL),
		OPT_BIT(0, "prune", &flags, N_("prune loose refs (default)"), PACK_REFS_PRUNE),
		OPT_END(),
	};
	git_config(git_default_config, NULL);
	if (parse_options(argc, argv, prefix, opts, pack_refs_usage, 0))
		usage_with_options(pack_refs_usage, opts);
	return refs_pack_refs(get_main_ref_store(the_repository), flags);
}