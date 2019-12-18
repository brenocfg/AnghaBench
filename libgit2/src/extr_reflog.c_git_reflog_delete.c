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
struct TYPE_4__ {TYPE_2__* backend; } ;
typedef  TYPE_1__ git_refdb ;
struct TYPE_5__ {int (* reflog_delete ) (TYPE_2__*,char const*) ;} ;

/* Variables and functions */
 int git_repository_refdb__weakptr (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,char const*) ; 

int git_reflog_delete(git_repository *repo, const char *name)
{
	git_refdb *refdb;
	int error;

	if ((error = git_repository_refdb__weakptr(&refdb, repo)) < 0)
		return -1;

	return refdb->backend->reflog_delete(refdb->backend, name);
}