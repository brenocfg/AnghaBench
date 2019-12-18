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
struct bufobj {int /*<<< orphan*/  bo_numoutput; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_BO_WLOCKED (struct bufobj*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

void
bufobj_wrefl(struct bufobj *bo)
{

	KASSERT(bo != NULL, ("NULL bo in bufobj_wref"));
	ASSERT_BO_WLOCKED(bo);
	bo->bo_numoutput++;
}