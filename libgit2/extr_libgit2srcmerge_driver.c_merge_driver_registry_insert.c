#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * driver; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_merge_driver_entry ;
typedef  int /*<<< orphan*/  git_merge_driver ;
struct TYPE_7__ {int /*<<< orphan*/  drivers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,scalar_t__) ; 
 int git_vector_insert_sorted (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__ merge_driver_registry ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int merge_driver_registry_insert(
	const char *name, git_merge_driver *driver)
{
	git_merge_driver_entry *entry;

	entry = git__calloc(1, sizeof(git_merge_driver_entry) + strlen(name) + 1);
	GIT_ERROR_CHECK_ALLOC(entry);

	strcpy(entry->name, name);
	entry->driver = driver;

	return git_vector_insert_sorted(
		&merge_driver_registry.drivers, entry, NULL);
}