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
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  head_oid; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_SUBMODULE_STATUS_IN_HEAD ; 
 int GIT_SUBMODULE_STATUS__HEAD_NOT_SUBMODULE ; 
 int GIT_SUBMODULE_STATUS__HEAD_OID_VALID ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void submodule_update_from_head_data(
	git_submodule *sm, mode_t mode, const git_oid *id)
{
	if (!S_ISGITLINK(mode))
		sm->flags |= GIT_SUBMODULE_STATUS__HEAD_NOT_SUBMODULE;
	else {
		git_oid_cpy(&sm->head_oid, id);

		sm->flags |= GIT_SUBMODULE_STATUS_IN_HEAD |
			GIT_SUBMODULE_STATUS__HEAD_OID_VALID;
	}
}