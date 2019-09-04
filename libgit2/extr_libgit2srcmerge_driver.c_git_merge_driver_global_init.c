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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  base; } ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  drivers; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  git__on_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_driver__binary ; 
 TYPE_3__ git_merge_driver__text ; 
 TYPE_2__ git_merge_driver__union ; 
 int /*<<< orphan*/  git_merge_driver_global_shutdown ; 
 scalar_t__ git_rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free_deep (int /*<<< orphan*/ *) ; 
 int git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_driver_entry_cmp ; 
 int /*<<< orphan*/  merge_driver_name__binary ; 
 int /*<<< orphan*/  merge_driver_name__text ; 
 int /*<<< orphan*/  merge_driver_name__union ; 
 TYPE_1__ merge_driver_registry ; 
 int merge_driver_registry_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int git_merge_driver_global_init(void)
{
	int error;

	if (git_rwlock_init(&merge_driver_registry.lock) < 0)
		return -1;

	if ((error = git_vector_init(&merge_driver_registry.drivers, 3,
		merge_driver_entry_cmp)) < 0)
		goto done;

	if ((error = merge_driver_registry_insert(
			merge_driver_name__text, &git_merge_driver__text.base)) < 0 ||
		(error = merge_driver_registry_insert(
			merge_driver_name__union, &git_merge_driver__union.base)) < 0 ||
		(error = merge_driver_registry_insert(
			merge_driver_name__binary, &git_merge_driver__binary)) < 0)
		goto done;

	git__on_shutdown(git_merge_driver_global_shutdown);

done:
	if (error < 0)
		git_vector_free_deep(&merge_driver_registry.drivers);

	return error;
}