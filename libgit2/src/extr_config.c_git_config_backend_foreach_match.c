#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_regexp ;
struct TYPE_12__ {scalar_t__ (* next ) (TYPE_2__**,TYPE_1__*) ;int /*<<< orphan*/  (* free ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ git_config_iterator ;
typedef  int (* git_config_foreach_cb ) (TYPE_2__*,void*) ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_config_entry ;
struct TYPE_14__ {int (* iterator ) (TYPE_1__**,TYPE_4__*) ;} ;
typedef  TYPE_4__ git_config_backend ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set_after_callback (int) ; 
 scalar_t__ git_regexp_compile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_regexp_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__**,TYPE_4__*) ; 
 scalar_t__ stub2 (TYPE_2__**,TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 

int git_config_backend_foreach_match(
	git_config_backend *backend,
	const char *regexp,
	git_config_foreach_cb cb,
	void *payload)
{
	git_config_entry *entry;
	git_config_iterator* iter;
	git_regexp regex;
	int error = 0;

	assert(backend && cb);

	if (regexp && git_regexp_compile(&regex, regexp, 0) < 0)
		return -1;

	if ((error = backend->iterator(&iter, backend)) < 0) {
		iter = NULL;
		return -1;
	}

	while (!(iter->next(&entry, iter) < 0)) {
		/* skip non-matching keys if regexp was provided */
		if (regexp && git_regexp_match(&regex, entry->name) != 0)
			continue;

		/* abort iterator on non-zero return value */
		if ((error = cb(entry, payload)) != 0) {
			git_error_set_after_callback(error);
			break;
		}
	}

	if (regexp != NULL)
		git_regexp_dispose(&regex);

	iter->free(iter);

	return error;
}