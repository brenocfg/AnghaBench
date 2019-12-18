#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct prison {int /*<<< orphan*/  pr_mtx; } ;
struct linux_prison {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PRISON ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (struct linux_prison*,struct linux_prison*,int) ; 
 int /*<<< orphan*/  free (struct linux_prison*,int /*<<< orphan*/ ) ; 
 struct linux_prison* linux_find_prison (struct prison*,struct prison**) ; 
 int /*<<< orphan*/  linux_osd_jail_slot ; 
 struct linux_prison* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd_free_reserved (void**) ; 
 int /*<<< orphan*/  osd_jail_set_reserved (struct prison*,int /*<<< orphan*/ ,void**,struct linux_prison*) ; 
 void** osd_reserve (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
linux_alloc_prison(struct prison *pr, struct linux_prison **lprp)
{
	struct prison *ppr;
	struct linux_prison *lpr, *nlpr;
	void **rsv;

	/* If this prison already has Linux info, return that. */
	lpr = linux_find_prison(pr, &ppr);
	if (ppr == pr)
		goto done;
	/*
	 * Allocate a new info record.  Then check again, in case something
	 * changed during the allocation.
	 */
	mtx_unlock(&ppr->pr_mtx);
	nlpr = malloc(sizeof(struct linux_prison), M_PRISON, M_WAITOK);
	rsv = osd_reserve(linux_osd_jail_slot);
	lpr = linux_find_prison(pr, &ppr);
	if (ppr == pr) {
		free(nlpr, M_PRISON);
		osd_free_reserved(rsv);
		goto done;
	}
	/* Inherit the initial values from the ancestor. */
	mtx_lock(&pr->pr_mtx);
	(void)osd_jail_set_reserved(pr, linux_osd_jail_slot, rsv, nlpr);
	bcopy(lpr, nlpr, sizeof(*lpr));
	lpr = nlpr;
	mtx_unlock(&ppr->pr_mtx);
 done:
	if (lprp != NULL)
		*lprp = lpr;
	else
		mtx_unlock(&pr->pr_mtx);
}