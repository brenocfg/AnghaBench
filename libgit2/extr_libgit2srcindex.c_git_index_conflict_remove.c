#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int index_conflict_remove (int /*<<< orphan*/ *,char const*) ; 

int git_index_conflict_remove(git_index *index, const char *path)
{
	assert(index && path);
	return index_conflict_remove(index, path);
}