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
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_4__ {scalar_t__ theirs; scalar_t__ ours; scalar_t__ ancestor; } ;
typedef  TYPE_1__ checkout_conflictdata ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 TYPE_1__* git_vector_get (int /*<<< orphan*/  const*,size_t) ; 

int checkout_conflictdata_empty(
	const git_vector *conflicts, size_t idx, void *payload)
{
	checkout_conflictdata *conflict;

	GIT_UNUSED(payload);

	if ((conflict = git_vector_get(conflicts, idx)) == NULL)
		return -1;

	if (conflict->ancestor || conflict->ours || conflict->theirs)
		return 0;

	git__free(conflict);
	return 1;
}