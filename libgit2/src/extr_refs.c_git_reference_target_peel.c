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
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  const peel; } ;
typedef  TYPE_1__ git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 scalar_t__ git_oid_is_zero (int /*<<< orphan*/  const*) ; 

const git_oid *git_reference_target_peel(const git_reference *ref)
{
	assert(ref);

	if (ref->type != GIT_REFERENCE_DIRECT || git_oid_is_zero(&ref->peel))
		return NULL;

	return &ref->peel;
}