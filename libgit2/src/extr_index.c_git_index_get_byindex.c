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
typedef  int /*<<< orphan*/  git_index_entry ;
struct TYPE_4__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  const* git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_vector_sort (int /*<<< orphan*/ *) ; 

const git_index_entry *git_index_get_byindex(
	git_index *index, size_t n)
{
	assert(index);
	git_vector_sort(&index->entries);
	return git_vector_get(&index->entries, n);
}