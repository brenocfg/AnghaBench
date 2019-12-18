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
struct set_gitdir_args {void* alternate_db; void* index_file; void* graft_file; void* object_dir; void* commondir; int /*<<< orphan*/ * member_0; } ;
struct argv_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERNATE_DB_ENVIRONMENT ; 
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  DB_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_COMMON_DIR_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_NAMESPACE_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_REPLACE_REF_BASE_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_SHALLOW_FILE_ENVIRONMENT ; 
 int /*<<< orphan*/  GRAFT_ENVIRONMENT ; 
 int /*<<< orphan*/  INDEX_ENVIRONMENT ; 
 int /*<<< orphan*/  NO_REPLACE_OBJECTS_ENVIRONMENT ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  expand_namespace (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 void* getenv_safe (struct argv_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_namespace ; 
 int /*<<< orphan*/  git_replace_ref_base ; 
 scalar_t__ read_replace_refs ; 
 int /*<<< orphan*/  repo_set_gitdir (int /*<<< orphan*/ ,char const*,struct set_gitdir_args*) ; 
 int /*<<< orphan*/  set_alternate_shallow_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void setup_git_env(const char *git_dir)
{
	const char *shallow_file;
	const char *replace_ref_base;
	struct set_gitdir_args args = { NULL };
	struct argv_array to_free = ARGV_ARRAY_INIT;

	args.commondir = getenv_safe(&to_free, GIT_COMMON_DIR_ENVIRONMENT);
	args.object_dir = getenv_safe(&to_free, DB_ENVIRONMENT);
	args.graft_file = getenv_safe(&to_free, GRAFT_ENVIRONMENT);
	args.index_file = getenv_safe(&to_free, INDEX_ENVIRONMENT);
	args.alternate_db = getenv_safe(&to_free, ALTERNATE_DB_ENVIRONMENT);
	repo_set_gitdir(the_repository, git_dir, &args);
	argv_array_clear(&to_free);

	if (getenv(NO_REPLACE_OBJECTS_ENVIRONMENT))
		read_replace_refs = 0;
	replace_ref_base = getenv(GIT_REPLACE_REF_BASE_ENVIRONMENT);
	free(git_replace_ref_base);
	git_replace_ref_base = xstrdup(replace_ref_base ? replace_ref_base
							  : "refs/replace/");
	free(git_namespace);
	git_namespace = expand_namespace(getenv(GIT_NAMESPACE_ENVIRONMENT));
	shallow_file = getenv(GIT_SHALLOW_FILE_ENVIRONMENT);
	if (shallow_file)
		set_alternate_shallow_file(the_repository, shallow_file, 0);
}