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
struct TYPE_4__ {TYPE_2__* backend; } ;
typedef  TYPE_1__ git_refdb ;
struct TYPE_5__ {int (* lock ) (void**,TYPE_2__*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int stub1 (void**,TYPE_2__*,char const*) ; 

int git_refdb_lock(void **payload, git_refdb *db, const char *refname)
{
	assert(payload && db && refname);

	if (!db->backend->lock) {
		git_error_set(GIT_ERROR_REFERENCE, "backend does not support locking");
		return -1;
	}

	return db->backend->lock(payload, db->backend, refname);
}