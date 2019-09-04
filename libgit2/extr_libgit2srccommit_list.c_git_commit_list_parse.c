#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int /*<<< orphan*/  odb; } ;
typedef  TYPE_2__ git_revwalk ;
struct TYPE_13__ {scalar_t__ type; } ;
struct TYPE_15__ {TYPE_1__ cached; } ;
typedef  TYPE_3__ git_odb_object ;
struct TYPE_16__ {int /*<<< orphan*/  oid; scalar_t__ parsed; } ;
typedef  TYPE_4__ git_commit_list_node ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 scalar_t__ GIT_OBJECT_COMMIT ; 
 int commit_quick_parse (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_odb_object_data (TYPE_3__*) ; 
 int /*<<< orphan*/  git_odb_object_free (TYPE_3__*) ; 
 int /*<<< orphan*/  git_odb_object_size (TYPE_3__*) ; 
 int git_odb_read (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int git_commit_list_parse(git_revwalk *walk, git_commit_list_node *commit)
{
	git_odb_object *obj;
	int error;

	if (commit->parsed)
		return 0;

	if ((error = git_odb_read(&obj, walk->odb, &commit->oid)) < 0)
		return error;

	if (obj->cached.type != GIT_OBJECT_COMMIT) {
		git_error_set(GIT_ERROR_INVALID, "object is no commit object");
		error = -1;
	} else
		error = commit_quick_parse(
			walk, commit,
			(const uint8_t *)git_odb_object_data(obj),
			git_odb_object_size(obj));

	git_odb_object_free(obj);
	return error;
}