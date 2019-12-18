#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* symbolic; int /*<<< orphan*/  oid; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  db; TYPE_1__ target; } ;
typedef  TYPE_2__ git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 int git_refdb_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*) ; 

int git_reference_delete(git_reference *ref)
{
	const git_oid *old_id = NULL;
	const char *old_target = NULL;

	if (ref->type == GIT_REFERENCE_DIRECT)
		old_id = &ref->target.oid;
	else
		old_target = ref->target.symbolic;

	return git_refdb_delete(ref->db, ref->name, old_id, old_target);
}