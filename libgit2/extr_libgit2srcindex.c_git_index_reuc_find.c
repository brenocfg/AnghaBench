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
struct TYPE_3__ {int /*<<< orphan*/  reuc_search; int /*<<< orphan*/  reuc; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int git_vector_bsearch2 (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

int git_index_reuc_find(size_t *at_pos, git_index *index, const char *path)
{
	return git_vector_bsearch2(at_pos, &index->reuc, index->reuc_search, path);
}