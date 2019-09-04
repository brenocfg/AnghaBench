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
 int index_find (size_t*,int /*<<< orphan*/ *,char const*,size_t,int) ; 

int git_index__find_pos(
	size_t *out, git_index *index, const char *path, size_t path_len, int stage)
{
	assert(index && path);
	return index_find(out, index, path, path_len, stage);
}