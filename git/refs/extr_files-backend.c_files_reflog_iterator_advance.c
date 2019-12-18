#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ref_iterator {int dummy; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/ * oid; int /*<<< orphan*/  refname; } ;
struct files_reflog_iterator {struct dir_iterator* dir_iterator; TYPE_3__ base; int /*<<< orphan*/  oid; int /*<<< orphan*/  ref_store; } ;
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  st_mode; } ;
struct dir_iterator {char* basename; int /*<<< orphan*/  relative_path; TYPE_2__ path; TYPE_1__ st; } ;

/* Variables and functions */
 int ITER_ERROR ; 
 int ITER_OK ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int dir_iterator_advance (struct dir_iterator*) ; 
 scalar_t__ ends_with (char*,char*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int ref_iterator_abort (struct ref_iterator*) ; 
 scalar_t__ refs_read_ref_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int files_reflog_iterator_advance(struct ref_iterator *ref_iterator)
{
	struct files_reflog_iterator *iter =
		(struct files_reflog_iterator *)ref_iterator;
	struct dir_iterator *diter = iter->dir_iterator;
	int ok;

	while ((ok = dir_iterator_advance(diter)) == ITER_OK) {
		int flags;

		if (!S_ISREG(diter->st.st_mode))
			continue;
		if (diter->basename[0] == '.')
			continue;
		if (ends_with(diter->basename, ".lock"))
			continue;

		if (refs_read_ref_full(iter->ref_store,
				       diter->relative_path, 0,
				       &iter->oid, &flags)) {
			error("bad ref for %s", diter->path.buf);
			continue;
		}

		iter->base.refname = diter->relative_path;
		iter->base.oid = &iter->oid;
		iter->base.flags = flags;
		return ITER_OK;
	}

	iter->dir_iterator = NULL;
	if (ref_iterator_abort(ref_iterator) == ITER_ERROR)
		ok = ITER_ERROR;
	return ok;
}