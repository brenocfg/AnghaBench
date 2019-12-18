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
struct TYPE_4__ {scalar_t__ refcnt; int /*<<< orphan*/  commit; int /*<<< orphan*/  blob; struct TYPE_4__* previous; } ;
typedef  TYPE_1__ git_blame__origin ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void origin_decref(git_blame__origin *o)
{
	if (o && --o->refcnt <= 0) {
		if (o->previous)
			origin_decref(o->previous);
		git_blob_free(o->blob);
		git_commit_free(o->commit);
		git__free(o);
	}
}