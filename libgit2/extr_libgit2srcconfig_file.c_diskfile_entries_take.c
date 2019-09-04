#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_entries ;
struct TYPE_3__ {int /*<<< orphan*/  values_mutex; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ diskfile_header ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git_config_entries_incref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static git_config_entries *diskfile_entries_take(diskfile_header *h)
{
	git_config_entries *entries;

	if (git_mutex_lock(&h->values_mutex) < 0) {
	    git_error_set(GIT_ERROR_OS, "failed to lock config backend");
	    return NULL;
	}

	entries = h->entries;
	git_config_entries_incref(entries);

	git_mutex_unlock(&h->values_mutex);

	return entries;
}