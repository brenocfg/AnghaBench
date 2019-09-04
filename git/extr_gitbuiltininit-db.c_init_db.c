#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int have_repository; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 unsigned int INIT_DB_EXIST_OK ; 
 unsigned int INIT_DB_QUIET ; 
 int OLD_PERM_EVERYBODY ; 
 int OLD_PERM_GROUP ; 
 int PERM_EVERYBODY ; 
 int PERM_GROUP ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  check_repository_format () ; 
 int create_default_files (char const*,char*) ; 
 int /*<<< orphan*/  create_object_directory () ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_git_dir () ; 
 int get_shared_repository () ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set (char*,char*) ; 
 int /*<<< orphan*/  git_init_db_config ; 
 int /*<<< orphan*/  init_is_bare_repository ; 
 int /*<<< orphan*/  is_bare_repository () ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  real_path (char const*) ; 
 char* real_pathdup (char const*,int) ; 
 int /*<<< orphan*/  safe_create_dir (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  separate_git_dir (char const*,char*) ; 
 int /*<<< orphan*/  set_git_dir (int /*<<< orphan*/ ) ; 
 TYPE_1__* startup_info ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int) ; 

int init_db(const char *git_dir, const char *real_git_dir,
	    const char *template_dir, unsigned int flags)
{
	int reinit;
	int exist_ok = flags & INIT_DB_EXIST_OK;
	char *original_git_dir = real_pathdup(git_dir, 1);

	if (real_git_dir) {
		struct stat st;

		if (!exist_ok && !stat(git_dir, &st))
			die(_("%s already exists"), git_dir);

		if (!exist_ok && !stat(real_git_dir, &st))
			die(_("%s already exists"), real_git_dir);

		set_git_dir(real_path(real_git_dir));
		git_dir = get_git_dir();
		separate_git_dir(git_dir, original_git_dir);
	}
	else {
		set_git_dir(real_path(git_dir));
		git_dir = get_git_dir();
	}
	startup_info->have_repository = 1;

	/* Just look for `core.hidedotfiles` */
	git_config(git_init_db_config, NULL);

	safe_create_dir(git_dir, 0);

	init_is_bare_repository = is_bare_repository();

	/* Check to see if the repository version is right.
	 * Note that a newly created repository does not have
	 * config file, so this will not fail.  What we are catching
	 * is an attempt to reinitialize new repository with an old tool.
	 */
	check_repository_format();

	reinit = create_default_files(template_dir, original_git_dir);

	create_object_directory();

	if (get_shared_repository()) {
		char buf[10];
		/* We do not spell "group" and such, so that
		 * the configuration can be read by older version
		 * of git. Note, we use octal numbers for new share modes,
		 * and compatibility values for PERM_GROUP and
		 * PERM_EVERYBODY.
		 */
		if (get_shared_repository() < 0)
			/* force to the mode value */
			xsnprintf(buf, sizeof(buf), "0%o", -get_shared_repository());
		else if (get_shared_repository() == PERM_GROUP)
			xsnprintf(buf, sizeof(buf), "%d", OLD_PERM_GROUP);
		else if (get_shared_repository() == PERM_EVERYBODY)
			xsnprintf(buf, sizeof(buf), "%d", OLD_PERM_EVERYBODY);
		else
			BUG("invalid value for shared_repository");
		git_config_set("core.sharedrepository", buf);
		git_config_set("receive.denyNonFastforwards", "true");
	}

	if (!(flags & INIT_DB_QUIET)) {
		int len = strlen(git_dir);

		if (reinit)
			printf(get_shared_repository()
			       ? _("Reinitialized existing shared Git repository in %s%s\n")
			       : _("Reinitialized existing Git repository in %s%s\n"),
			       git_dir, len && git_dir[len-1] != '/' ? "/" : "");
		else
			printf(get_shared_repository()
			       ? _("Initialized empty shared Git repository in %s%s\n")
			       : _("Initialized empty Git repository in %s%s\n"),
			       git_dir, len && git_dir[len-1] != '/' ? "/" : "");
	}

	free(original_git_dir);
	return 0;
}