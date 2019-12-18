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
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int git_iterator_current (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iterator_current(
	const git_index_entry **entry,
	git_iterator *iterator)
{
	int error;

	if ((error = git_iterator_current(entry, iterator)) == GIT_ITEROVER) {
		*entry = NULL;
		error = 0;
	}

	return error;
}