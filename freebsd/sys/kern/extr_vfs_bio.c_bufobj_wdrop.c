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
struct bufobj {scalar_t__ bo_numoutput; int bo_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 int BO_WWAIT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

void
bufobj_wdrop(struct bufobj *bo)
{

	KASSERT(bo != NULL, ("NULL bo in bufobj_wdrop"));
	BO_LOCK(bo);
	KASSERT(bo->bo_numoutput > 0, ("bufobj_wdrop non-positive count"));
	if ((--bo->bo_numoutput == 0) && (bo->bo_flag & BO_WWAIT)) {
		bo->bo_flag &= ~BO_WWAIT;
		wakeup(&bo->bo_numoutput);
	}
	BO_UNLOCK(bo);
}