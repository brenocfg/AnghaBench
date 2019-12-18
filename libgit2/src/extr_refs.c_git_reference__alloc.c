#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {int /*<<< orphan*/  peel; TYPE_1__ target; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFERENCE_DIRECT ; 
 TYPE_2__* alloc_ref (char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

git_reference *git_reference__alloc(
	const char *name,
	const git_oid *oid,
	const git_oid *peel)
{
	git_reference *ref;

	assert(name && oid);

	ref = alloc_ref(name);
	if (!ref)
		return NULL;

	ref->type = GIT_REFERENCE_DIRECT;
	git_oid_cpy(&ref->target.oid, oid);

	if (peel != NULL)
		git_oid_cpy(&ref->peel, peel);

	return ref;
}