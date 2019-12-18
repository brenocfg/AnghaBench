#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* ref_name; int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ git_reflog ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 TYPE_1__* git__strdup (char const*) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reflog_alloc(git_reflog **reflog, const char *name)
{
	git_reflog *log;

	*reflog = NULL;

	log = git__calloc(1, sizeof(git_reflog));
	GIT_ERROR_CHECK_ALLOC(log);

	log->ref_name = git__strdup(name);
	GIT_ERROR_CHECK_ALLOC(log->ref_name);

	if (git_vector_init(&log->entries, 0, NULL) < 0) {
		git__free(log->ref_name);
		git__free(log);
		return -1;
	}

	*reflog = log;

	return 0;
}