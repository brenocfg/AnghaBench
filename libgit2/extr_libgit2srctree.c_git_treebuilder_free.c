#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ git_treebuilder ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_strmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_treebuilder_clear (TYPE_1__*) ; 

void git_treebuilder_free(git_treebuilder *bld)
{
	if (bld == NULL)
		return;

	git_treebuilder_clear(bld);
	git_strmap_free(bld->map);
	git__free(bld);
}