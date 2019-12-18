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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_5__ {TYPE_2__* backend; } ;
typedef  TYPE_1__ git_refdb ;
struct TYPE_6__ {int (* unlock ) (TYPE_2__*,void*,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int stub1 (TYPE_2__*,void*,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*) ; 

int git_refdb_unlock(git_refdb *db, void *payload, int success, int update_reflog, const git_reference *ref, const git_signature *sig, const char *message)
{
	assert(db);

	return db->backend->unlock(db->backend, payload, success, update_reflog, ref, sig, message);
}