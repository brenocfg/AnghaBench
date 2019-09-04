#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ path; scalar_t__ name; struct TYPE_5__* branch; struct TYPE_5__* url; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ git_submodule ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git__memzero (TYPE_1__*,int) ; 

__attribute__((used)) static void submodule_release(git_submodule *sm)
{
	if (!sm)
		return;

	if (sm->repo) {
		sm->repo = NULL;
	}

	if (sm->path != sm->name)
		git__free(sm->path);
	git__free(sm->name);
	git__free(sm->url);
	git__free(sm->branch);
	git__memzero(sm, sizeof(*sm));
	git__free(sm);
}