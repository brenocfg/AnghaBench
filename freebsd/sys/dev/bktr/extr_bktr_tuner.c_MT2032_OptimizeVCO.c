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
typedef  int /*<<< orphan*/  bktr_ptr_t ;

/* Variables and functions */
 int MT2032_CheckLOLock (int /*<<< orphan*/ ) ; 
 int MT2032_GetRegister (int) ; 
 int /*<<< orphan*/  MT2032_SetRegister (int,int) ; 

__attribute__((used)) static int 
MT2032_OptimizeVCO(bktr_ptr_t bktr, int sel, int lock)
{
	int             tad1, lo1a;

	tad1 = MT2032_GetRegister(0x0f) & 0x07;

	if (tad1 == 0) {
		return lock;
	}
	if (tad1 == 1) {
		return lock;
	}
	if (tad1 == 2) {
		if (sel == 0) {
			return lock;
		} else {
			sel--;
		}
	} else {
		if (sel < 4) {
			sel++;
		} else {
			return lock;
		}
	}
	lo1a = MT2032_GetRegister(0x01) & 0x07;
	MT2032_SetRegister(0x01, lo1a | (sel << 4));
	lock = MT2032_CheckLOLock(bktr);
	return lock;
}