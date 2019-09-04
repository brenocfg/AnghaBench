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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 char* git__strdup (char const*) ; 
 int note_get_default_ref (char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int normalize_namespace(char **out, git_repository *repo, const char *notes_ref)
{
	if (notes_ref) {
		*out = git__strdup(notes_ref);
		GIT_ERROR_CHECK_ALLOC(*out);
		return 0;
	}

	return note_get_default_ref(out, repo);
}