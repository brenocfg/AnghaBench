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
struct dmar_unit {int /*<<< orphan*/  qi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int DMAR_CCMD_CIRG_GLOB ; 
 int DMAR_CCMD_ICC ; 
 int DMAR_CCMD_ICC32 ; 
 scalar_t__ DMAR_CCMD_REG ; 
 int /*<<< orphan*/  DMAR_WAIT_UNTIL (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int dmar_read4 (struct dmar_unit*,scalar_t__) ; 
 int /*<<< orphan*/  dmar_write8 (struct dmar_unit*,scalar_t__,int) ; 

int
dmar_inv_ctx_glob(struct dmar_unit *unit)
{
	int error;

	/*
	 * Access to the CCMD register must be serialized while the
	 * command is submitted.
	 */
	DMAR_ASSERT_LOCKED(unit);
	KASSERT(!unit->qi_enabled, ("QI enabled"));

	/*
	 * The DMAR_CCMD_ICC bit in the upper dword should be written
	 * after the low dword write is completed.  Amd64
	 * dmar_write8() does not have this issue, i386 dmar_write8()
	 * writes the upper dword last.
	 */
	dmar_write8(unit, DMAR_CCMD_REG, DMAR_CCMD_ICC | DMAR_CCMD_CIRG_GLOB);
	DMAR_WAIT_UNTIL(((dmar_read4(unit, DMAR_CCMD_REG + 4) & DMAR_CCMD_ICC32)
	    == 0));
	return (error);
}