#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  repo; TYPE_2__* opts; } ;
typedef  TYPE_1__ tag_state ;
struct TYPE_8__ {char* tag_name; } ;
typedef  TYPE_2__ tag_options ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_9__ {char* ptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  check (int,char*) ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_short_id (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tag_delete (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static void action_delete_tag(tag_state *state)
{
	tag_options *opts = state->opts;
	git_object *obj;
	git_buf abbrev_oid = {0};

	check(!opts->tag_name, "Name required");

	check_lg2(git_revparse_single(&obj, state->repo, opts->tag_name),
			"Failed to lookup rev", opts->tag_name);

	check_lg2(git_object_short_id(&abbrev_oid, obj),
			"Unable to get abbreviated OID", opts->tag_name);

	check_lg2(git_tag_delete(state->repo, opts->tag_name),
			"Unable to delete tag", opts->tag_name);

	printf("Deleted tag '%s' (was %s)\n", opts->tag_name, abbrev_oid.ptr);

	git_buf_dispose(&abbrev_oid);
	git_object_free(obj);
}