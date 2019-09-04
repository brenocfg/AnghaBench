#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ident_email; int /*<<< orphan*/  ident_name; } ;
typedef  TYPE_1__ git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__strdup (char const*) ; 
 char* git__swap (int /*<<< orphan*/ ,char*) ; 

int git_repository_set_ident(git_repository *repo, const char *name, const char *email)
{
	char *tmp_name = NULL, *tmp_email = NULL;

	if (name) {
		tmp_name = git__strdup(name);
		GIT_ERROR_CHECK_ALLOC(tmp_name);
	}

	if (email) {
		tmp_email = git__strdup(email);
		GIT_ERROR_CHECK_ALLOC(tmp_email);
	}

	tmp_name = git__swap(repo->ident_name, tmp_name);
	tmp_email = git__swap(repo->ident_email, tmp_email);

	git__free(tmp_name);
	git__free(tmp_email);

	return 0;
}