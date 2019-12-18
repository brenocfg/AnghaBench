#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  symbolic; } ;
struct TYPE_10__ {TYPE_2__ target; int /*<<< orphan*/  name; TYPE_1__* db; } ;
typedef  TYPE_3__ git_reference ;
struct TYPE_8__ {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int ensure_is_an_updatable_symbolic_reference (TYPE_3__*) ; 
 int git_reference_symbolic_create_matching (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,char const*) ; 

int git_reference_symbolic_set_target(
	git_reference **out,
	git_reference *ref,
	const char *target,
	const char *log_message)
{
	int error;

	assert(out && ref && target);

	if ((error = ensure_is_an_updatable_symbolic_reference(ref)) < 0)
		return error;

	return git_reference_symbolic_create_matching(
		out, ref->db->repo, ref->name, target, 1, ref->target.symbolic, log_message);
}