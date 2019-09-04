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
struct TYPE_6__ {int /*<<< orphan*/ * symbolic; } ;
struct TYPE_7__ {TYPE_1__ target; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFERENCE_SYMBOLIC ; 
 TYPE_2__* alloc_ref (char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int /*<<< orphan*/ * git__strdup (char const*) ; 

git_reference *git_reference__alloc_symbolic(
	const char *name, const char *target)
{
	git_reference *ref;

	assert(name && target);

	ref = alloc_ref(name);
	if (!ref)
		return NULL;

	ref->type = GIT_REFERENCE_SYMBOLIC;

	if ((ref->target.symbolic = git__strdup(target)) == NULL) {
		git__free(ref);
		return NULL;
	}

	return ref;
}