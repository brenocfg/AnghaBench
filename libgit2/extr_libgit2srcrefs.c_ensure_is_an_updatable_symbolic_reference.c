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
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ensure_is_an_updatable_symbolic_reference(git_reference *ref)
{
	if (ref->type == GIT_REFERENCE_SYMBOLIC)
		return 0;

	git_error_set(GIT_ERROR_REFERENCE, "cannot set symbolic target on a direct reference");
	return -1;
}