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
struct pathspec {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int PATHSPEC_PREFER_FULL ; 
 int PATHSPEC_PREFIX_ORIGIN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_oid_committish (char const*,struct object_id*) ; 
 int /*<<< orphan*/  get_oid_treeish (char const*,struct object_id*) ; 
 int /*<<< orphan*/  parse_pathspec (struct pathspec*,int /*<<< orphan*/ ,int,char const*,char const**) ; 
 scalar_t__ read_cache () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  verify_filename (char const*,char const*,int) ; 
 int /*<<< orphan*/  verify_non_filename (char const*,char const*) ; 

__attribute__((used)) static void parse_args(struct pathspec *pathspec,
		       const char **argv, const char *prefix,
		       int patch_mode,
		       const char **rev_ret)
{
	const char *rev = "HEAD";
	struct object_id unused;
	/*
	 * Possible arguments are:
	 *
	 * git reset [-opts] [<rev>]
	 * git reset [-opts] <tree> [<paths>...]
	 * git reset [-opts] <tree> -- [<paths>...]
	 * git reset [-opts] -- [<paths>...]
	 * git reset [-opts] <paths>...
	 *
	 * At this point, argv points immediately after [-opts].
	 */

	if (argv[0]) {
		if (!strcmp(argv[0], "--")) {
			argv++; /* reset to HEAD, possibly with paths */
		} else if (argv[1] && !strcmp(argv[1], "--")) {
			rev = argv[0];
			argv += 2;
		}
		/*
		 * Otherwise, argv[0] could be either <rev> or <paths> and
		 * has to be unambiguous. If there is a single argument, it
		 * can not be a tree
		 */
		else if ((!argv[1] && !get_oid_committish(argv[0], &unused)) ||
			 (argv[1] && !get_oid_treeish(argv[0], &unused))) {
			/*
			 * Ok, argv[0] looks like a commit/tree; it should not
			 * be a filename.
			 */
			verify_non_filename(prefix, argv[0]);
			rev = *argv++;
		} else {
			/* Otherwise we treat this as a filename */
			verify_filename(prefix, argv[0], 1);
		}
	}
	*rev_ret = rev;

	if (read_cache() < 0)
		die(_("index file corrupt"));

	parse_pathspec(pathspec, 0,
		       PATHSPEC_PREFER_FULL |
		       (patch_mode ? PATHSPEC_PREFIX_ORIGIN : 0),
		       prefix, argv);
}