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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_get_string (char const**,int /*<<< orphan*/ *,char*) ; 
 int git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_signature_now (int /*<<< orphan*/ **,char const*,char const*) ; 

int git_signature_default(git_signature **out, git_repository *repo)
{
	int error;
	git_config *cfg;
	const char *user_name, *user_email;

	if ((error = git_repository_config_snapshot(&cfg, repo)) < 0)
		return error;

	if (!(error = git_config_get_string(&user_name, cfg, "user.name")) &&
		!(error = git_config_get_string(&user_email, cfg, "user.email")))
		error = git_signature_now(out, user_name, user_email);

	git_config_free(cfg);
	return error;
}