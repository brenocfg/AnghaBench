#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* opts; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ tag_state ;
struct TYPE_5__ {char* target; int /*<<< orphan*/  force; int /*<<< orphan*/  tag_name; } ;
typedef  TYPE_2__ tag_options ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  check (int,char*) ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tag_create_lightweight (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void action_create_lighweight_tag(tag_state *state)
{
	git_repository *repo = state->repo;
	tag_options *opts = state->opts;
	git_oid oid;
	git_object *target;

	check(!opts->tag_name, "Name required");

	if (!opts->target) opts->target = "HEAD";

	check(!opts->target, "Target required");

	check_lg2(git_revparse_single(&target, repo, opts->target),
			"Unable to resolve spec", opts->target);

	check_lg2(git_tag_create_lightweight(&oid, repo, opts->tag_name,
				target, opts->force), "Unable to create tag", NULL);

	git_object_free(target);
}