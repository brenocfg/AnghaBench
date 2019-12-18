#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;
struct TYPE_7__ {TYPE_1__ rules; } ;
typedef  TYPE_2__ git_attr_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ATTR_FILE__IN_MEMORY ; 
 int /*<<< orphan*/  GIT_IGNORE_DEFAULT_RULES ; 
 int /*<<< orphan*/  GIT_IGNORE_INTERNAL ; 
 int git_attr_cache__get (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int git_attr_cache__init (int /*<<< orphan*/ *) ; 
 int parse_ignore_file (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_internal_ignores(git_attr_file **out, git_repository *repo)
{
	int error;

	if ((error = git_attr_cache__init(repo)) < 0)
		return error;

	error = git_attr_cache__get(out, repo, NULL, GIT_ATTR_FILE__IN_MEMORY, NULL,
				    GIT_IGNORE_INTERNAL, NULL, false);

	/* if internal rules list is empty, insert default rules */
	if (!error && !(*out)->rules.length)
		error = parse_ignore_file(repo, *out, GIT_IGNORE_DEFAULT_RULES, false);

	return error;
}