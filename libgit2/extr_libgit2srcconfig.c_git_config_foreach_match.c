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
typedef  int /*<<< orphan*/  git_config_iterator ;
typedef  int (* git_config_foreach_cb ) (int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  git_config_iterator_free (int /*<<< orphan*/ *) ; 
 int git_config_iterator_glob_new (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,char const*) ; 
 int git_config_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set_after_callback (int) ; 

int git_config_foreach_match(
	const git_config *cfg,
	const char *regexp,
	git_config_foreach_cb cb,
	void *payload)
{
	int error;
	git_config_iterator *iter;
	git_config_entry *entry;

	if ((error = git_config_iterator_glob_new(&iter, cfg, regexp)) < 0)
		return error;

	while (!(error = git_config_next(&entry, iter))) {
		if ((error = cb(entry, payload)) != 0) {
			git_error_set_after_callback(error);
			break;
		}
	}

	git_config_iterator_free(iter);

	if (error == GIT_ITEROVER)
		error = 0;

	return error;
}