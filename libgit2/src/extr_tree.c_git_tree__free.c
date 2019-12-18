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
struct TYPE_3__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  odb_obj; } ;
typedef  TYPE_1__ git_tree ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_array_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ ) ; 

void git_tree__free(void *_tree)
{
	git_tree *tree = _tree;

	git_odb_object_free(tree->odb_obj);
	git_array_clear(tree->entries);
	git__free(tree);
}