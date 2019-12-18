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
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/ * owner; } ;
struct TYPE_5__ {int do_fsync; TYPE_1__ rc; } ;
typedef  TYPE_2__ git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIGMAP_FSYNCOBJECTFILES ; 
 int /*<<< orphan*/  GIT_ERROR_ODB ; 
 int GIT_ODB_CAP_FROM_OWNER ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository__configmap_lookup (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_odb__set_caps(git_odb *odb, int caps)
{
	if (caps == GIT_ODB_CAP_FROM_OWNER) {
		git_repository *repo = odb->rc.owner;
		int val;

		if (!repo) {
			git_error_set(GIT_ERROR_ODB, "cannot access repository to set odb caps");
			return -1;
		}

		if (!git_repository__configmap_lookup(&val, repo, GIT_CONFIGMAP_FSYNCOBJECTFILES))
			odb->do_fsync = !!val;
	}

	return 0;
}