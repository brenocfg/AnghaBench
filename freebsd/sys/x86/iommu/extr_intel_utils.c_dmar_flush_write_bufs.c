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
struct dmar_unit {int hw_cap; int hw_gcmd; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int DMAR_CAP_RWBF ; 
 int /*<<< orphan*/  DMAR_GCMD_REG ; 
 int DMAR_GCMD_WBF ; 
 int /*<<< orphan*/  DMAR_GSTS_REG ; 
 int DMAR_GSTS_WBFS ; 
 int /*<<< orphan*/  DMAR_WAIT_UNTIL (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int dmar_read4 (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_write4 (struct dmar_unit*,int /*<<< orphan*/ ,int) ; 

int
dmar_flush_write_bufs(struct dmar_unit *unit)
{
	int error;

	DMAR_ASSERT_LOCKED(unit);

	/*
	 * DMAR_GCMD_WBF is only valid when CAP_RWBF is reported.
	 */
	KASSERT((unit->hw_cap & DMAR_CAP_RWBF) != 0,
	    ("dmar%d: no RWBF", unit->unit));

	dmar_write4(unit, DMAR_GCMD_REG, unit->hw_gcmd | DMAR_GCMD_WBF);
	DMAR_WAIT_UNTIL(((dmar_read4(unit, DMAR_GSTS_REG) & DMAR_GSTS_WBFS)
	    != 0));
	return (error);
}