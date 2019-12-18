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
typedef  int /*<<< orphan*/  uint32_t ;
struct dmar_unit {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_HAS_QI (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_IECTL_IM ; 
 int /*<<< orphan*/  DMAR_IECTL_REG ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmar_read4 (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_write4 (struct dmar_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dmar_enable_qi_intr(struct dmar_unit *unit)
{
	uint32_t iectl;

	DMAR_ASSERT_LOCKED(unit);
	KASSERT(DMAR_HAS_QI(unit), ("dmar%d: QI is not supported", unit->unit));
	iectl = dmar_read4(unit, DMAR_IECTL_REG);
	iectl &= ~DMAR_IECTL_IM;
	dmar_write4(unit, DMAR_IECTL_REG, iectl);
}