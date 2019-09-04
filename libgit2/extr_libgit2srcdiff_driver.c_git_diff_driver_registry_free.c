#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  drivers; } ;
typedef  TYPE_1__ git_diff_driver_registry ;
typedef  int /*<<< orphan*/  git_diff_driver ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_driver_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strmap_foreach_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strmap_free (int /*<<< orphan*/ ) ; 

void git_diff_driver_registry_free(git_diff_driver_registry *reg)
{
	git_diff_driver *drv;

	if (!reg)
		return;

	git_strmap_foreach_value(reg->drivers, drv, git_diff_driver_free(drv));
	git_strmap_free(reg->drivers);
	git__free(reg);
}