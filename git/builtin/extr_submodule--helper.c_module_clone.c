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
struct string_list {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct option {int dummy; } ;

/* Variables and functions */
 char const* N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,char const*) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,char const*,char const*) ; 
 struct option OPT_STRING_LIST (int /*<<< orphan*/ ,char*,struct string_list*,char const*,char const*) ; 
 struct option OPT__QUIET (int*,char*) ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* absolute_pathdup (int /*<<< orphan*/ ) ; 
 scalar_t__ clone_submodule (char*,char*,char const*,char const*,struct string_list*,int,int,int) ; 
 int /*<<< orphan*/  connect_work_tree_and_git_dir (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  file_exists (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 int /*<<< orphan*/  get_git_work_tree () ; 
 int /*<<< orphan*/  git_config_get_string (char*,char**) ; 
 int /*<<< orphan*/  git_config_set_in_file (char*,char*,char*) ; 
 char* git_pathdup_submodule (char*,char*) ; 
 int /*<<< orphan*/  is_absolute_path (char*) ; 
 int parse_options (int,char const**,char const*,struct option*,char const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_possible_alternates (char const*,struct string_list*) ; 
 scalar_t__ safe_create_leading_directories_const (char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,...) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int module_clone(int argc, const char **argv, const char *prefix)
{
	const char *name = NULL, *url = NULL, *depth = NULL;
	int quiet = 0;
	int progress = 0;
	char *p, *path = NULL, *sm_gitdir;
	struct strbuf sb = STRBUF_INIT;
	struct string_list reference = STRING_LIST_INIT_NODUP;
	int dissociate = 0;
	char *sm_alternate = NULL, *error_strategy = NULL;

	struct option module_clone_options[] = {
		OPT_STRING(0, "prefix", &prefix,
			   N_("path"),
			   N_("alternative anchor for relative paths")),
		OPT_STRING(0, "path", &path,
			   N_("path"),
			   N_("where the new submodule will be cloned to")),
		OPT_STRING(0, "name", &name,
			   N_("string"),
			   N_("name of the new submodule")),
		OPT_STRING(0, "url", &url,
			   N_("string"),
			   N_("url where to clone the submodule from")),
		OPT_STRING_LIST(0, "reference", &reference,
			   N_("repo"),
			   N_("reference repository")),
		OPT_BOOL(0, "dissociate", &dissociate,
			   N_("use --reference only while cloning")),
		OPT_STRING(0, "depth", &depth,
			   N_("string"),
			   N_("depth for shallow clones")),
		OPT__QUIET(&quiet, "Suppress output for cloning a submodule"),
		OPT_BOOL(0, "progress", &progress,
			   N_("force cloning progress")),
		OPT_END()
	};

	const char *const git_submodule_helper_usage[] = {
		N_("git submodule--helper clone [--prefix=<path>] [--quiet] "
		   "[--reference <repository>] [--name <name>] [--depth <depth>] "
		   "--url <url> --path <path>"),
		NULL
	};

	argc = parse_options(argc, argv, prefix, module_clone_options,
			     git_submodule_helper_usage, 0);

	if (argc || !url || !path || !*path)
		usage_with_options(git_submodule_helper_usage,
				   module_clone_options);

	strbuf_addf(&sb, "%s/modules/%s", get_git_dir(), name);
	sm_gitdir = absolute_pathdup(sb.buf);
	strbuf_reset(&sb);

	if (!is_absolute_path(path)) {
		strbuf_addf(&sb, "%s/%s", get_git_work_tree(), path);
		path = strbuf_detach(&sb, NULL);
	} else
		path = xstrdup(path);

	if (!file_exists(sm_gitdir)) {
		if (safe_create_leading_directories_const(sm_gitdir) < 0)
			die(_("could not create directory '%s'"), sm_gitdir);

		prepare_possible_alternates(name, &reference);

		if (clone_submodule(path, sm_gitdir, url, depth, &reference, dissociate,
				    quiet, progress))
			die(_("clone of '%s' into submodule path '%s' failed"),
			    url, path);
	} else {
		if (safe_create_leading_directories_const(path) < 0)
			die(_("could not create directory '%s'"), path);
		strbuf_addf(&sb, "%s/index", sm_gitdir);
		unlink_or_warn(sb.buf);
		strbuf_reset(&sb);
	}

	connect_work_tree_and_git_dir(path, sm_gitdir, 0);

	p = git_pathdup_submodule(path, "config");
	if (!p)
		die(_("could not get submodule directory for '%s'"), path);

	/* setup alternateLocation and alternateErrorStrategy in the cloned submodule if needed */
	git_config_get_string("submodule.alternateLocation", &sm_alternate);
	if (sm_alternate)
		git_config_set_in_file(p, "submodule.alternateLocation",
					   sm_alternate);
	git_config_get_string("submodule.alternateErrorStrategy", &error_strategy);
	if (error_strategy)
		git_config_set_in_file(p, "submodule.alternateErrorStrategy",
					   error_strategy);

	free(sm_alternate);
	free(error_strategy);

	strbuf_release(&sb);
	free(sm_gitdir);
	free(path);
	free(p);
	return 0;
}