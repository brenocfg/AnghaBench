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
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  iterator__has_been_accessed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterator_set_ignore_case (int /*<<< orphan*/ *,int) ; 

void git_iterator_set_ignore_case(git_iterator *i, bool ignore_case)
{
	assert(!iterator__has_been_accessed(i));
	iterator_set_ignore_case(i, ignore_case);
}