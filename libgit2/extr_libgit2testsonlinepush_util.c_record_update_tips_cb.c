#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  new_oid; int /*<<< orphan*/  old_oid; struct TYPE_7__* name; } ;
typedef  TYPE_1__ updated_tip ;
struct TYPE_8__ {int /*<<< orphan*/  updated_tips; } ;
typedef  TYPE_2__ record_callbacks_data ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,int) ; 
 TYPE_1__* git__strdup (char const*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

int record_update_tips_cb(const char *refname, const git_oid *a, const git_oid *b, void *data)
{
	updated_tip *t;
	record_callbacks_data *record_data = (record_callbacks_data *)data;

	cl_assert(t = git__calloc(1, sizeof(*t)));

	cl_assert(t->name = git__strdup(refname));
	git_oid_cpy(&t->old_oid, a);
	git_oid_cpy(&t->new_oid, b);

	git_vector_insert(&record_data->updated_tips, t);

	return 0;
}