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
typedef  int /*<<< orphan*/  vm_page_t ;
struct dmar_unit {int hw_gcmd; int /*<<< orphan*/  ctx_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_GCMD_REG ; 
 int DMAR_GCMD_SRTP ; 
 int /*<<< orphan*/  DMAR_GSTS_REG ; 
 int DMAR_GSTS_RTPS ; 
 int /*<<< orphan*/  DMAR_RTADDR_REG ; 
 int /*<<< orphan*/  DMAR_WAIT_UNTIL (int) ; 
 int /*<<< orphan*/  VM_OBJECT_RLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int dmar_read4 (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_write4 (struct dmar_unit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmar_write8 (struct dmar_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dmar_load_root_entry_ptr(struct dmar_unit *unit)
{
	vm_page_t root_entry;
	int error;

	/*
	 * Access to the GCMD register must be serialized while the
	 * command is submitted.
	 */
	DMAR_ASSERT_LOCKED(unit);

	VM_OBJECT_RLOCK(unit->ctx_obj);
	root_entry = vm_page_lookup(unit->ctx_obj, 0);
	VM_OBJECT_RUNLOCK(unit->ctx_obj);
	dmar_write8(unit, DMAR_RTADDR_REG, VM_PAGE_TO_PHYS(root_entry));
	dmar_write4(unit, DMAR_GCMD_REG, unit->hw_gcmd | DMAR_GCMD_SRTP);
	DMAR_WAIT_UNTIL(((dmar_read4(unit, DMAR_GSTS_REG) & DMAR_GSTS_RTPS)
	    != 0));
	return (error);
}