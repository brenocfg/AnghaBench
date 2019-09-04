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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  repo_version_string ;
typedef  int /*<<< orphan*/  junk ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  GIT_REPO_VERSION ; 
 scalar_t__ LOG_REFS_UNSET ; 
 int /*<<< orphan*/  R_OK ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISLNK (int) ; 
 int S_IXUSR ; 
 int TEST_FILEMODE ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_shared_perm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_templates (char const*) ; 
 scalar_t__ create_symref (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 char* get_git_work_tree () ; 
 scalar_t__ get_shared_repository () ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_clear () ; 
 int /*<<< orphan*/  git_config_set (char*,char const*) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  git_init_db_config ; 
 int /*<<< orphan*/  git_path (char*) ; 
 char* git_path_buf (struct strbuf*,char*) ; 
 int /*<<< orphan*/ * init_db_template_dir ; 
 int /*<<< orphan*/  init_is_bare_repository ; 
 int init_shared_repository ; 
 scalar_t__ is_bare_repository () ; 
 int /*<<< orphan*/  is_bare_repository_cfg ; 
 scalar_t__ log_all_ref_updates ; 
 int /*<<< orphan*/  lstat (char*,struct stat*) ; 
 scalar_t__ needs_work_tree_config (char const*,char const*) ; 
 int /*<<< orphan*/  probe_utf8_pathname_composition () ; 
 int readlink (char*,char*,int) ; 
 scalar_t__ refs_init_db (struct strbuf*) ; 
 int /*<<< orphan*/  reset_shared_repository () ; 
 int /*<<< orphan*/  safe_create_dir (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_shared_repository (int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  symlink (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  xmkstemp (char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_default_files(const char *template_path,
				const char *original_git_dir)
{
	struct stat st1;
	struct strbuf buf = STRBUF_INIT;
	char *path;
	char repo_version_string[10];
	char junk[2];
	int reinit;
	int filemode;
	struct strbuf err = STRBUF_INIT;

	/* Just look for `init.templatedir` */
	init_db_template_dir = NULL; /* re-set in case it was set before */
	git_config(git_init_db_config, NULL);

	/*
	 * First copy the templates -- we might have the default
	 * config file there, in which case we would want to read
	 * from it after installing.
	 *
	 * Before reading that config, we also need to clear out any cached
	 * values (since we've just potentially changed what's available on
	 * disk).
	 */
	copy_templates(template_path);
	git_config_clear();
	reset_shared_repository();
	git_config(git_default_config, NULL);

	/*
	 * We must make sure command-line options continue to override any
	 * values we might have just re-read from the config.
	 */
	is_bare_repository_cfg = init_is_bare_repository;
	if (init_shared_repository != -1)
		set_shared_repository(init_shared_repository);

	/*
	 * We would have created the above under user's umask -- under
	 * shared-repository settings, we would need to fix them up.
	 */
	if (get_shared_repository()) {
		adjust_shared_perm(get_git_dir());
	}

	/*
	 * We need to create a "refs" dir in any case so that older
	 * versions of git can tell that this is a repository.
	 */
	safe_create_dir(git_path("refs"), 1);
	adjust_shared_perm(git_path("refs"));

	if (refs_init_db(&err))
		die("failed to set up refs db: %s", err.buf);

	/*
	 * Create the default symlink from ".git/HEAD" to the "master"
	 * branch, if it does not exist yet.
	 */
	path = git_path_buf(&buf, "HEAD");
	reinit = (!access(path, R_OK)
		  || readlink(path, junk, sizeof(junk)-1) != -1);
	if (!reinit) {
		if (create_symref("HEAD", "refs/heads/master", NULL) < 0)
			exit(1);
	}

	/* This forces creation of new config file */
	xsnprintf(repo_version_string, sizeof(repo_version_string),
		  "%d", GIT_REPO_VERSION);
	git_config_set("core.repositoryformatversion", repo_version_string);

	/* Check filemode trustability */
	path = git_path_buf(&buf, "config");
	filemode = TEST_FILEMODE;
	if (TEST_FILEMODE && !lstat(path, &st1)) {
		struct stat st2;
		filemode = (!chmod(path, st1.st_mode ^ S_IXUSR) &&
				!lstat(path, &st2) &&
				st1.st_mode != st2.st_mode &&
				!chmod(path, st1.st_mode));
		if (filemode && !reinit && (st1.st_mode & S_IXUSR))
			filemode = 0;
	}
	git_config_set("core.filemode", filemode ? "true" : "false");

	if (is_bare_repository())
		git_config_set("core.bare", "true");
	else {
		const char *work_tree = get_git_work_tree();
		git_config_set("core.bare", "false");
		/* allow template config file to override the default */
		if (log_all_ref_updates == LOG_REFS_UNSET)
			git_config_set("core.logallrefupdates", "true");
		if (needs_work_tree_config(original_git_dir, work_tree))
			git_config_set("core.worktree", work_tree);
	}

	if (!reinit) {
		/* Check if symlink is supported in the work tree */
		path = git_path_buf(&buf, "tXXXXXX");
		if (!close(xmkstemp(path)) &&
		    !unlink(path) &&
		    !symlink("testing", path) &&
		    !lstat(path, &st1) &&
		    S_ISLNK(st1.st_mode))
			unlink(path); /* good */
		else
			git_config_set("core.symlinks", "false");

		/* Check if the filesystem is case-insensitive */
		path = git_path_buf(&buf, "CoNfIg");
		if (!access(path, F_OK))
			git_config_set("core.ignorecase", "true");
		probe_utf8_pathname_composition();
	}

	strbuf_release(&buf);
	return reinit;
}