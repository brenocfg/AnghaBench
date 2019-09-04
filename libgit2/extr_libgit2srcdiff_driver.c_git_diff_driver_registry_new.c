#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  drivers; } ;
typedef  TYPE_1__ git_diff_driver_registry ;

/* Variables and functions */
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_diff_driver_registry_free (TYPE_1__*) ; 
 scalar_t__ git_strmap_new (int /*<<< orphan*/ *) ; 

git_diff_driver_registry *git_diff_driver_registry_new(void)
{
	git_diff_driver_registry *reg =
		git__calloc(1, sizeof(git_diff_driver_registry));
	if (!reg)
		return NULL;

	if (git_strmap_new(&reg->drivers) < 0) {
		git_diff_driver_registry_free(reg);
		return NULL;
	}

	return reg;
}