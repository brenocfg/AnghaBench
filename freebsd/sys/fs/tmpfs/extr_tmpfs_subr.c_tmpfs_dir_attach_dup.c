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
struct tmpfs_dir_duphead {int dummy; } ;
struct TYPE_4__ {struct tmpfs_dir_duphead tn_dupindex; } ;
struct tmpfs_node {TYPE_1__ tn_dir; } ;
struct tmpfs_dirent {scalar_t__ td_cookie; } ;
struct TYPE_5__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  index_entries; } ;
struct TYPE_6__ {TYPE_2__ td_dup; } ;

/* Variables and functions */
 struct tmpfs_dirent* LIST_FIRST (struct tmpfs_dir_duphead*) ; 
 int /*<<< orphan*/  LIST_INSERT_AFTER (struct tmpfs_dirent*,struct tmpfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_BEFORE (struct tmpfs_dirent*,struct tmpfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct tmpfs_dir_duphead*,struct tmpfs_dirent*,int /*<<< orphan*/ ) ; 
 struct tmpfs_dirent* LIST_NEXT (struct tmpfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ TMPFS_DIRCOOKIE_DUP_MAX ; 
 scalar_t__ TMPFS_DIRCOOKIE_DUP_MIN ; 
 int tmpfs_dirent_dup (struct tmpfs_dirent*) ; 
 TYPE_3__ uh ; 

__attribute__((used)) static void
tmpfs_dir_attach_dup(struct tmpfs_node *dnode,
    struct tmpfs_dir_duphead *duphead, struct tmpfs_dirent *nde)
{
	struct tmpfs_dir_duphead *dupindex;
	struct tmpfs_dirent *de, *pde;

	dupindex = &dnode->tn_dir.tn_dupindex;
	de = LIST_FIRST(dupindex);
	if (de == NULL || de->td_cookie < TMPFS_DIRCOOKIE_DUP_MAX) {
		if (de == NULL)
			nde->td_cookie = TMPFS_DIRCOOKIE_DUP_MIN;
		else
			nde->td_cookie = de->td_cookie + 1;
		MPASS(tmpfs_dirent_dup(nde));
		LIST_INSERT_HEAD(dupindex, nde, uh.td_dup.index_entries);
		LIST_INSERT_HEAD(duphead, nde, uh.td_dup.entries);
		return;
	}

	/*
	 * Cookie numbers are near exhaustion. Scan dupindex list for unused
	 * numbers. dupindex list is sorted in descending order. Keep it so
	 * after inserting nde.
	 */
	while (1) {
		pde = de;
		de = LIST_NEXT(de, uh.td_dup.index_entries);
		if (de == NULL && pde->td_cookie != TMPFS_DIRCOOKIE_DUP_MIN) {
			/*
			 * Last element of the index doesn't have minimal cookie
			 * value, use it.
			 */
			nde->td_cookie = TMPFS_DIRCOOKIE_DUP_MIN;
			LIST_INSERT_AFTER(pde, nde, uh.td_dup.index_entries);
			LIST_INSERT_HEAD(duphead, nde, uh.td_dup.entries);
			return;
		} else if (de == NULL) {
			/*
			 * We are so lucky have 2^30 hash duplicates in single
			 * directory :) Return largest possible cookie value.
			 * It should be fine except possible issues with
			 * VOP_READDIR restart.
			 */
			nde->td_cookie = TMPFS_DIRCOOKIE_DUP_MAX;
			LIST_INSERT_HEAD(dupindex, nde,
			    uh.td_dup.index_entries);
			LIST_INSERT_HEAD(duphead, nde, uh.td_dup.entries);
			return;
		}
		if (de->td_cookie + 1 == pde->td_cookie ||
		    de->td_cookie >= TMPFS_DIRCOOKIE_DUP_MAX)
			continue;	/* No hole or invalid cookie. */
		nde->td_cookie = de->td_cookie + 1;
		MPASS(tmpfs_dirent_dup(nde));
		MPASS(pde->td_cookie > nde->td_cookie);
		MPASS(nde->td_cookie > de->td_cookie);
		LIST_INSERT_BEFORE(de, nde, uh.td_dup.index_entries);
		LIST_INSERT_HEAD(duphead, nde, uh.td_dup.entries);
		return;
	}
}