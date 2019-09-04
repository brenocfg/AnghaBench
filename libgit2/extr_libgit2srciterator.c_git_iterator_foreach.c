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
typedef  int (* git_iterator_foreach_cb ) (int /*<<< orphan*/  const*,void*) ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int git_iterator_advance (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int git_iterator_current (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

int git_iterator_foreach(
	git_iterator *iterator,
	git_iterator_foreach_cb cb,
	void *data)
{
	const git_index_entry *iterator_item;
	int error = 0;

	if ((error = git_iterator_current(&iterator_item, iterator)) < 0)
		goto done;

	if ((error = cb(iterator_item, data)) != 0)
		goto done;

	while (true) {
		if ((error = git_iterator_advance(&iterator_item, iterator)) < 0)
			goto done;

		if ((error = cb(iterator_item, data)) != 0)
			goto done;
	}

done:
	if (error == GIT_ITEROVER)
		error = 0;

	return error;
}