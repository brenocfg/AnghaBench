#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* db; } ;
typedef  TYPE_2__ git_reference ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_8__ {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_2__*) ; 
 scalar_t__ git_reference_resolve (TYPE_2__**,TYPE_2__*) ; 
 int /*<<< orphan*/  git_reference_target (TYPE_2__*) ; 

__attribute__((used)) static int object_from_reference(git_object **object, git_reference *reference)
{
	git_reference *resolved = NULL;
	int error;

	if (git_reference_resolve(&resolved, reference) < 0)
		return -1;

	error = git_object_lookup(object, reference->db->repo, git_reference_target(resolved), GIT_OBJECT_ANY);
	git_reference_free(resolved);

	return error;
}