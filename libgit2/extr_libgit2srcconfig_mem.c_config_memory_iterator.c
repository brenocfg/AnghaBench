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
typedef  int /*<<< orphan*/  git_config_entries ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_2__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ config_memory_backend ;

/* Variables and functions */
 int git_config_entries_dup (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_entries_free (int /*<<< orphan*/ *) ; 
 int git_config_entries_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int config_memory_iterator(
	git_config_iterator **iter,
	git_config_backend *backend)
{
	config_memory_backend *memory_backend = (config_memory_backend *) backend;
	git_config_entries *entries;
	int error;

	if ((error = git_config_entries_dup(&entries, memory_backend->entries)) < 0)
		goto out;

	if ((error = git_config_entries_iterator_new(iter, entries)) < 0)
		goto out;

out:
	/* Let iterator delete duplicated entries when it's done */
	git_config_entries_free(entries);
	return error;
}