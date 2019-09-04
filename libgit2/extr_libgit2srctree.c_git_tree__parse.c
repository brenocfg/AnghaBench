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
struct TYPE_3__ {int /*<<< orphan*/  odb_obj; } ;
typedef  TYPE_1__ git_tree ;
typedef  int /*<<< orphan*/  git_odb_object ;

/* Variables and functions */
 int /*<<< orphan*/  git_odb_object_data (int /*<<< orphan*/ *) ; 
 scalar_t__ git_odb_object_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_size (int /*<<< orphan*/ *) ; 
 scalar_t__ git_tree__parse_raw (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_tree__parse(void *_tree, git_odb_object *odb_obj)
{
	git_tree *tree = _tree;

	if ((git_tree__parse_raw(tree,
	    git_odb_object_data(odb_obj),
	    git_odb_object_size(odb_obj))) < 0)
		return -1;

	if (git_odb_object_dup(&tree->odb_obj, odb_obj) < 0)
		return -1;

	return 0;
}