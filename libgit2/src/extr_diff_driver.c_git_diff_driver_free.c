#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  word_pattern; int /*<<< orphan*/  fn_patterns; } ;
typedef  TYPE_1__ git_diff_driver ;
struct TYPE_6__ {int /*<<< orphan*/  re; } ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_array_clear (int /*<<< orphan*/ ) ; 
 TYPE_3__* git_array_get (int /*<<< orphan*/ ,size_t) ; 
 size_t git_array_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_dispose (int /*<<< orphan*/ *) ; 

void git_diff_driver_free(git_diff_driver *driver)
{
	size_t i;

	if (!driver)
		return;

	for (i = 0; i < git_array_size(driver->fn_patterns); ++i)
		git_regexp_dispose(& git_array_get(driver->fn_patterns, i)->re);
	git_array_clear(driver->fn_patterns);

	git_regexp_dispose(&driver->word_pattern);

	git__free(driver);
}