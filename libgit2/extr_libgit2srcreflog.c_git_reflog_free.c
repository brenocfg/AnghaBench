#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reflog_entry ;
struct TYPE_7__ {size_t length; } ;
struct TYPE_6__ {struct TYPE_6__* ref_name; TYPE_2__ entries; scalar_t__ db; } ;
typedef  TYPE_1__ git_reflog ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_DEC (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_refdb__free ; 
 int /*<<< orphan*/  git_reflog_entry__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * git_vector_get (TYPE_2__*,size_t) ; 

void git_reflog_free(git_reflog *reflog)
{
	size_t i;
	git_reflog_entry *entry;

	if (reflog == NULL)
		return;

	if (reflog->db)
		GIT_REFCOUNT_DEC(reflog->db, git_refdb__free);

	for (i=0; i < reflog->entries.length; i++) {
		entry = git_vector_get(&reflog->entries, i);

		git_reflog_entry__free(entry);
	}

	git_vector_free(&reflog->entries);
	git__free(reflog->ref_name);
	git__free(reflog);
}