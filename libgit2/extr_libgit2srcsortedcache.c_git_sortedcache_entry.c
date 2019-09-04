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
struct TYPE_3__ {int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ git_sortedcache ;

/* Variables and functions */
 void* git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_vector_is_sorted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_sort (int /*<<< orphan*/ *) ; 

void *git_sortedcache_entry(git_sortedcache *sc, size_t pos)
{
	/* make sure the items are sorted so this gets the correct item */
	if (!git_vector_is_sorted(&sc->items))
		git_vector_sort(&sc->items);

	return git_vector_get(&sc->items, pos);
}