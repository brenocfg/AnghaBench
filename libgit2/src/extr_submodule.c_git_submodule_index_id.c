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
struct TYPE_4__ {int flags; int /*<<< orphan*/  const index_oid; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_SUBMODULE_STATUS__INDEX_OID_VALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

const git_oid *git_submodule_index_id(git_submodule *submodule)
{
	assert(submodule);

	if (submodule->flags & GIT_SUBMODULE_STATUS__INDEX_OID_VALID)
		return &submodule->index_oid;
	else
		return NULL;
}