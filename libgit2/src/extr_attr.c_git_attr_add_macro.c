#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_pool ;
struct TYPE_10__ {int /*<<< orphan*/  flags; TYPE_2__* pattern; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {int /*<<< orphan*/  assigns; TYPE_1__ match; } ;
typedef  TYPE_2__ git_attr_rule ;
struct TYPE_12__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ATTR_FNMATCH_MACRO ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 TYPE_2__* git__calloc (int,int) ; 
 int git_attr_assignment__parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 int git_attr_cache__init (int /*<<< orphan*/ *) ; 
 int git_attr_cache__insert_macro (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_attr_rule__free (TYPE_2__*) ; 
 TYPE_2__* git_pool_strdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_4__* git_repository_attr_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (TYPE_2__*) ; 

int git_attr_add_macro(
	git_repository *repo,
	const char *name,
	const char *values)
{
	int error;
	git_attr_rule *macro = NULL;
	git_pool *pool;

	if ((error = git_attr_cache__init(repo)) < 0)
		return error;

	macro = git__calloc(1, sizeof(git_attr_rule));
	GIT_ERROR_CHECK_ALLOC(macro);

	pool = &git_repository_attr_cache(repo)->pool;

	macro->match.pattern = git_pool_strdup(pool, name);
	GIT_ERROR_CHECK_ALLOC(macro->match.pattern);

	macro->match.length = strlen(macro->match.pattern);
	macro->match.flags = GIT_ATTR_FNMATCH_MACRO;

	error = git_attr_assignment__parse(repo, pool, &macro->assigns, &values);

	if (!error)
		error = git_attr_cache__insert_macro(repo, macro);

	if (error < 0)
		git_attr_rule__free(macro);

	return error;
}