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
typedef  int u_char ;
typedef  int /*<<< orphan*/  bktr_ptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int MT2032_CheckLOLock (int /*<<< orphan*/ ) ; 
 int MT2032_ComputeFreq (int,int,int,int,int,int*,int*,int) ; 
 scalar_t__ MT2032_OPTIMIZE_VCO ; 
 int MT2032_OptimizeVCO (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MT2032_SetRegister (int,int) ; 
 int MT2032_XOGC ; 
 int /*<<< orphan*/  TDA9887_init (int /*<<< orphan*/ ,int) ; 
 char* bktr_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
MT2032_SetIFFreq(bktr_ptr_t bktr, int rfin, int if1, int if2, int from, int to)
{
	u_char          buf[21];
	int             lint_try, sel, lock = 0;

	if (MT2032_ComputeFreq(rfin, if1, if2, from, to, &buf[0], &sel, MT2032_XOGC) == -1)
		return -1;

	TDA9887_init(bktr, 0);

	/* send only the relevant registers per Rev. 1.2 */
	MT2032_SetRegister(0, buf[0x00]);
	MT2032_SetRegister(1, buf[0x01]);
	MT2032_SetRegister(2, buf[0x02]);

	MT2032_SetRegister(5, buf[0x05]);
	MT2032_SetRegister(6, buf[0x06]);
	MT2032_SetRegister(7, buf[0x07]);

	MT2032_SetRegister(11, buf[0x0B]);
	MT2032_SetRegister(12, buf[0x0C]);

	/* wait for PLLs to lock (per manual), retry LINT if not. */
	for (lint_try = 0; lint_try < 2; lint_try++) {
		lock = MT2032_CheckLOLock(bktr);

		if (MT2032_OPTIMIZE_VCO) {
			lock = MT2032_OptimizeVCO(bktr, sel, lock);
		}
		if (lock == 6) {
			break;
		}
		/* set LINT to re-init PLLs */
		MT2032_SetRegister(7, 0x80 + 8 + MT2032_XOGC);
		DELAY(10000);
		MT2032_SetRegister(7, 8 + MT2032_XOGC);
	}
	if (lock != 6)
		printf("%s: PLL didn't lock\n", bktr_name(bktr));

	MT2032_SetRegister(2, 0x20);

	TDA9887_init(bktr, 1);
	return 0;
}