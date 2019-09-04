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
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index_entry ;
typedef  int /*<<< orphan*/  checkout_data ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int checkout_action_wd_only (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int checkout_remaining_wd_items(
	checkout_data *data,
	git_iterator *workdir,
	const git_index_entry *wd,
	git_vector *spec)
{
	int error = 0;

	while (wd && !error)
		error = checkout_action_wd_only(data, workdir, &wd, spec);

	if (error == GIT_ITEROVER)
		error = 0;

	return error;
}