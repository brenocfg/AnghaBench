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
struct TYPE_5__ {char const* symbolic; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ target; } ;
typedef  TYPE_2__ git_reference ;

/* Variables and functions */
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 

const char *git_reference_symbolic_target(const git_reference *ref)
{
	assert(ref);

	if (ref->type != GIT_REFERENCE_SYMBOLIC)
		return NULL;

	return ref->target.symbolic;
}