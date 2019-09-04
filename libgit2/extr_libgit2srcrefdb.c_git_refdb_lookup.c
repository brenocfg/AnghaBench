#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* db; } ;
typedef  TYPE_1__ git_reference ;
struct TYPE_9__ {TYPE_4__* backend; } ;
typedef  TYPE_2__ git_refdb ;
struct TYPE_10__ {int (* lookup ) (TYPE_1__**,TYPE_4__*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__**,TYPE_4__*,char const*) ; 

int git_refdb_lookup(git_reference **out, git_refdb *db, const char *ref_name)
{
	git_reference *ref;
	int error;

	assert(db && db->backend && out && ref_name);

	error = db->backend->lookup(&ref, db->backend, ref_name);
	if (error < 0)
		return error;

	GIT_REFCOUNT_INC(db);
	ref->db = db;

	*out = ref;
	return 0;
}