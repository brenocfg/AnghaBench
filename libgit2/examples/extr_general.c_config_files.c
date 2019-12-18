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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
#define  GIT_ENOTFOUND 128 
 int /*<<< orphan*/  check_error (int,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_get_int32 (int*,int /*<<< orphan*/ *,char*) ; 
 int git_config_get_string (char const**,int /*<<< orphan*/ *,char*) ; 
 int git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static void config_files(const char *repo_path, git_repository* repo)
{
	const char *email;
	char config_path[256];
	int32_t autocorrect;
	git_config *cfg;
	git_config *snap_cfg;
	int error_code;

	printf("\n*Config Listing*\n");

	/**
	 * Open a config object so we can read global values from it.
	 */
	sprintf(config_path, "%s/config", repo_path);
	check_error(git_config_open_ondisk(&cfg, config_path), "opening config");

	if (git_config_get_int32(&autocorrect, cfg, "help.autocorrect") == 0)
		printf("Autocorrect: %d\n", autocorrect);

	check_error(git_repository_config_snapshot(&snap_cfg, repo), "config snapshot");
	git_config_get_string(&email, snap_cfg, "user.email");
	printf("Email: %s\n", email);

	error_code = git_config_get_int32(&autocorrect, cfg, "help.autocorrect");
	switch (error_code)
	{
		case 0:
			printf("Autocorrect: %d\n", autocorrect);
			break;
		case GIT_ENOTFOUND:
			printf("Autocorrect: Undefined\n");
			break;
		default:
			check_error(error_code, "get_int32 failed");
	}
	git_config_free(cfg);

	check_error(git_repository_config_snapshot(&snap_cfg, repo), "config snapshot");
	error_code = git_config_get_string(&email, snap_cfg, "user.email");
	switch (error_code)
	{
		case 0:
			printf("Email: %s\n", email);
			break;
		case GIT_ENOTFOUND:
			printf("Email: Undefined\n");
			break;
		default:
			check_error(error_code, "get_string failed");
	}

	git_config_free(snap_cfg);
}