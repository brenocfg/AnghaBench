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
 int /*<<< orphan*/  DELAY (int) ; 
 int MT2032_GetRegister (int) ; 

__attribute__((used)) static int 
MT2032_CheckLOLock(bktr_ptr_t bktr)
{
	int             t, lock = 0;
	for (t = 0; t < 10; t++) {
		lock = MT2032_GetRegister(0x0e) & 0x06;
		if (lock == 6) {
			break;
		}
		DELAY(1000);
	}
	return lock;
}