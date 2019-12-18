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
typedef  int /*<<< orphan*/  git_transport ;
struct TYPE_5__ {int /*<<< orphan*/  free; int /*<<< orphan*/  close; int /*<<< orphan*/  action; } ;
struct TYPE_6__ {TYPE_1__ parent; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_2__ git_subtransport ;
typedef  int /*<<< orphan*/  git_smart_subtransport ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  _git_action ; 
 int /*<<< orphan*/  _git_close ; 
 int /*<<< orphan*/  _git_free ; 
 TYPE_2__* git__calloc (int,int) ; 

int git_smart_subtransport_git(git_smart_subtransport **out, git_transport *owner, void *param)
{
	git_subtransport *t;

	GIT_UNUSED(param);

	if (!out)
		return -1;

	t = git__calloc(1, sizeof(git_subtransport));
	GIT_ERROR_CHECK_ALLOC(t);

	t->owner = owner;
	t->parent.action = _git_action;
	t->parent.close = _git_close;
	t->parent.free = _git_free;

	*out = (git_smart_subtransport *) t;
	return 0;
}