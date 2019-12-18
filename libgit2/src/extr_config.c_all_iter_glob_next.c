#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_iterator ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_config_entry ;
struct TYPE_6__ {int /*<<< orphan*/  regex; } ;
typedef  TYPE_2__ all_iter ;

/* Variables and functions */
 int all_iter_next (TYPE_1__**,int /*<<< orphan*/ *) ; 
 scalar_t__ git_regexp_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int all_iter_glob_next(git_config_entry **entry, git_config_iterator *_iter)
{
	int error;
	all_iter *iter = (all_iter *) _iter;

	/*
	 * We use the "normal" function to grab the next one across
	 * backends and then apply the regex
	 */
	while ((error = all_iter_next(entry, _iter)) == 0) {
		/* skip non-matching keys if regexp was provided */
		if (git_regexp_match(&iter->regex, (*entry)->name) != 0)
			continue;

		/* and simply return if we like the entry's name */
		return 0;
	}

	return error;
}