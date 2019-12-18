#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t count; int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ git_strarray ;
struct TYPE_6__ {int /*<<< orphan*/  pathlist; } ;
typedef  TYPE_2__ git_iterator ;

/* Variables and functions */
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iterator_pathlist_init(git_iterator *iter, git_strarray *pathlist)
{
	size_t i;

	if (git_vector_init(&iter->pathlist, pathlist->count, NULL) < 0)
		return -1;

	for (i = 0; i < pathlist->count; i++) {
		if (!pathlist->strings[i])
			continue;

		if (git_vector_insert(&iter->pathlist, pathlist->strings[i]) < 0)
			return -1;
	}

	return 0;
}