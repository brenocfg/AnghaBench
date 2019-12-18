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
struct bufobj {scalar_t__ bo_numoutput; int /*<<< orphan*/  bo_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_BO_WLOCKED (struct bufobj*) ; 
 int /*<<< orphan*/  BO_LOCKPTR (struct bufobj*) ; 
 int /*<<< orphan*/  BO_WWAIT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int PRIBIO ; 
 int msleep (scalar_t__*,int /*<<< orphan*/ ,int,char*,int) ; 

int
bufobj_wwait(struct bufobj *bo, int slpflag, int timeo)
{
	int error;

	KASSERT(bo != NULL, ("NULL bo in bufobj_wwait"));
	ASSERT_BO_WLOCKED(bo);
	error = 0;
	while (bo->bo_numoutput) {
		bo->bo_flag |= BO_WWAIT;
		error = msleep(&bo->bo_numoutput, BO_LOCKPTR(bo),
		    slpflag | (PRIBIO + 1), "bo_wwait", timeo);
		if (error)
			break;
	}
	return (error);
}