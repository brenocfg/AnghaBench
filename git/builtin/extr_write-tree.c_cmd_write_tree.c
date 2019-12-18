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
struct option {char* member_2; int* member_3; int member_6; int /*<<< orphan*/  member_8; int /*<<< orphan*/ * member_7; int /*<<< orphan*/  member_5; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  OPTION_BIT ; 
 struct option OPT_BIT (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PARSE_OPT_HIDDEN ; 
 int PARSE_OPT_NOARG ; 
 int /*<<< orphan*/  WRITE_TREE_IGNORE_CACHE_TREE ; 
 int /*<<< orphan*/  WRITE_TREE_MISSING_OK ; 
#define  WRITE_TREE_PREFIX_ERROR 130 
#define  WRITE_TREE_UNMERGED_INDEX 129 
#define  WRITE_TREE_UNREADABLE_INDEX 128 
 int /*<<< orphan*/  die (char*,char const*,...) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 char* oid_to_hex (struct object_id*) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int write_cache_as_tree (struct object_id*,int,char const*) ; 
 int /*<<< orphan*/  write_tree_usage ; 

int cmd_write_tree(int argc, const char **argv, const char *cmd_prefix)
{
	int flags = 0, ret;
	const char *tree_prefix = NULL;
	struct object_id oid;
	const char *me = "git-write-tree";
	struct option write_tree_options[] = {
		OPT_BIT(0, "missing-ok", &flags, N_("allow missing objects"),
			WRITE_TREE_MISSING_OK),
		OPT_STRING(0, "prefix", &tree_prefix, N_("<prefix>/"),
			   N_("write tree object for a subdirectory <prefix>")),
		{ OPTION_BIT, 0, "ignore-cache-tree", &flags, NULL,
		  N_("only useful for debugging"),
		  PARSE_OPT_HIDDEN | PARSE_OPT_NOARG, NULL,
		  WRITE_TREE_IGNORE_CACHE_TREE },
		OPT_END()
	};

	git_config(git_default_config, NULL);
	argc = parse_options(argc, argv, cmd_prefix, write_tree_options,
			     write_tree_usage, 0);

	ret = write_cache_as_tree(&oid, flags, tree_prefix);
	switch (ret) {
	case 0:
		printf("%s\n", oid_to_hex(&oid));
		break;
	case WRITE_TREE_UNREADABLE_INDEX:
		die("%s: error reading the index", me);
		break;
	case WRITE_TREE_UNMERGED_INDEX:
		die("%s: error building trees", me);
		break;
	case WRITE_TREE_PREFIX_ERROR:
		die("%s: prefix %s not found", me, tree_prefix);
		break;
	}
	return ret;
}