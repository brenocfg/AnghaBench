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
struct TYPE_6__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_7__ {int /*<<< orphan*/  remove_conflicts; } ;
typedef  TYPE_2__ checkout_data ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char const*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* git__strdup (int /*<<< orphan*/ ) ; 
 int git_vector_insert (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int checkout_conflict_append_remove(
	const git_index_entry *ancestor,
	const git_index_entry *ours,
	const git_index_entry *theirs,
	void *payload)
{
	checkout_data *data = payload;
	const char *name;

	assert(ancestor || ours || theirs);

	if (ancestor)
		name = git__strdup(ancestor->path);
	else if (ours)
		name = git__strdup(ours->path);
	else if (theirs)
		name = git__strdup(theirs->path);
	else
		abort();

	GIT_ERROR_CHECK_ALLOC(name);

	return git_vector_insert(&data->remove_conflicts, (char *)name);
}