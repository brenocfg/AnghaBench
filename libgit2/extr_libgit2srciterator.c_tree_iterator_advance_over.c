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
typedef  int /*<<< orphan*/  git_iterator_status_t ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_STATUS_NORMAL ; 
 int git_iterator_advance (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tree_iterator_advance_over(
	const git_index_entry **out,
	git_iterator_status_t *status,
	git_iterator *i)
{
	*status = GIT_ITERATOR_STATUS_NORMAL;
	return git_iterator_advance(out, i);
}