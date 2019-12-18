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
typedef  int /*<<< orphan*/  git_reference_iterator ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int git_refdb_iterator_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_reference_next(git_reference **out, git_reference_iterator *iter)
{
	return git_refdb_iterator_next(out, iter);
}