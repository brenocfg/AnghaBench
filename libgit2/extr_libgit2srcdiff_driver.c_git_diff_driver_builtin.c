#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  drivers; } ;
typedef  TYPE_1__ git_diff_driver_registry ;
struct TYPE_13__ {int flags; scalar_t__ words; scalar_t__ fns; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_diff_driver_definition ;
struct TYPE_14__ {int /*<<< orphan*/  name; int /*<<< orphan*/  word_pattern; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ git_diff_driver ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  DIFF_DRIVER_PATTERNLIST ; 
 int REG_EXTENDED ; 
 TYPE_2__* builtin_defs ; 
 int diff_driver_add_patterns (TYPE_3__*,scalar_t__,int) ; 
 int diff_driver_alloc (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_driver_free (TYPE_3__*) ; 
 int git_error_set_regex (int /*<<< orphan*/ *,int) ; 
 int git_strmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int p_regcomp (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_diff_driver_builtin(
	git_diff_driver **out,
	git_diff_driver_registry *reg,
	const char *driver_name)
{
	git_diff_driver_definition *ddef = NULL;
	git_diff_driver *drv = NULL;
	int error = 0;
	size_t idx;

	for (idx = 0; idx < ARRAY_SIZE(builtin_defs); ++idx) {
		if (!strcasecmp(driver_name, builtin_defs[idx].name)) {
			ddef = &builtin_defs[idx];
			break;
		}
	}
	if (!ddef)
		goto done;

	if ((error = diff_driver_alloc(&drv, NULL, ddef->name)) < 0)
		goto done;

	drv->type = DIFF_DRIVER_PATTERNLIST;

	if (ddef->fns &&
		(error = diff_driver_add_patterns(
			drv, ddef->fns, ddef->flags | REG_EXTENDED)) < 0)
		goto done;

	if (ddef->words &&
		(error = p_regcomp(
			&drv->word_pattern, ddef->words, ddef->flags | REG_EXTENDED)))
	{
		error = git_error_set_regex(&drv->word_pattern, error);
		goto done;
	}

	if ((error = git_strmap_set(reg->drivers, drv->name, drv)) < 0)
		goto done;

done:
	if (error && drv)
		git_diff_driver_free(drv);
	else
		*out = drv;

	return error;
}