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
typedef  int uint32_t ;
struct dmar_unit {int /*<<< orphan*/  hw_cap; } ;

/* Variables and functions */
 int DMAR_CAP_FRO (int /*<<< orphan*/ ) ; 
 int DMAR_CAP_NFR (int /*<<< orphan*/ ) ; 
 int DMAR_FRCD2_F32 ; 
 int DMAR_FSTS_REG ; 
 int dmar_read4 (struct dmar_unit*,int) ; 
 int /*<<< orphan*/  dmar_write4 (struct dmar_unit*,int,int) ; 

__attribute__((used)) static void
dmar_clear_faults(struct dmar_unit *unit)
{
	uint32_t frec, frir, fsts;
	int i;

	for (i = 0; i < DMAR_CAP_NFR(unit->hw_cap); i++) {
		frir = (DMAR_CAP_FRO(unit->hw_cap) + i) * 16;
		frec = dmar_read4(unit, frir + 12);
		if ((frec & DMAR_FRCD2_F32) == 0)
			continue;
		dmar_write4(unit, frir + 12, DMAR_FRCD2_F32);
	}
	fsts = dmar_read4(unit, DMAR_FSTS_REG);
	dmar_write4(unit, DMAR_FSTS_REG, fsts);
}