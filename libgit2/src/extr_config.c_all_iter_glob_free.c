#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_iterator ;
struct TYPE_2__ {int /*<<< orphan*/  regex; } ;
typedef  TYPE_1__ all_iter ;

/* Variables and functions */
 int /*<<< orphan*/  all_iter_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_regexp_dispose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void all_iter_glob_free(git_config_iterator *_iter)
{
	all_iter *iter = (all_iter *) _iter;

	git_regexp_dispose(&iter->regex);
	all_iter_free(_iter);
}