#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ git_treebuilder ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 size_t git_strmap_size (int /*<<< orphan*/ ) ; 

size_t git_treebuilder_entrycount(git_treebuilder *bld)
{
	assert(bld);

	return git_strmap_size(bld->map);
}