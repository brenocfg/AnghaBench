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
 int /*<<< orphan*/  GIT_ITERATOR_STATUS_EMPTY ; 
 int empty_iterator_noop (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int empty_iterator_advance_over(
	const git_index_entry **e,
	git_iterator_status_t *s,
	git_iterator *i)
{
	*s = GIT_ITERATOR_STATUS_EMPTY;
	return empty_iterator_noop(e, i);
}