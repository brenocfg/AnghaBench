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
struct rs_iomap_mr {scalar_t__ index; int /*<<< orphan*/ * mr; int /*<<< orphan*/  entry; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int atomic_fetch_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dlist_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct rs_iomap_mr*) ; 
 int /*<<< orphan*/  ibv_dereg_mr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_release_iomap_mr(struct rs_iomap_mr *iomr)
{
	if (atomic_fetch_sub(&iomr->refcnt, 1) != 1)
		return;

	dlist_remove(&iomr->entry);
	ibv_dereg_mr(iomr->mr);
	if (iomr->index >= 0)
		iomr->mr = NULL;
	else
		free(iomr);
}