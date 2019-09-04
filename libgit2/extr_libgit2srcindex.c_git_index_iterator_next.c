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
struct TYPE_3__ {scalar_t__ cur; int /*<<< orphan*/  snap; } ;
typedef  TYPE_1__ git_index_iterator ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git_vector_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_vector_length (int /*<<< orphan*/ *) ; 

int git_index_iterator_next(
	const git_index_entry **out,
	git_index_iterator *it)
{
	assert(out && it);

	if (it->cur >= git_vector_length(&it->snap))
		return GIT_ITEROVER;

	*out = (git_index_entry *)git_vector_get(&it->snap, it->cur++);
	return 0;
}