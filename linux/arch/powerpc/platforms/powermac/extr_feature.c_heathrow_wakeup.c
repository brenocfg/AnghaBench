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
struct macio_chip {int dummy; } ;

/* Variables and functions */
 int HRW_IOBUS_ENABLE ; 
 int /*<<< orphan*/  MACIO_IN32 (int) ; 
 int /*<<< orphan*/  MACIO_OUT32 (int,int) ; 
 int /*<<< orphan*/  dbdma_restore (struct macio_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  save_alt_dbdma ; 
 int /*<<< orphan*/  save_dbdma ; 
 int* save_fcr ; 
 int save_mbcr ; 

__attribute__((used)) static void heathrow_wakeup(struct macio_chip *macio, int secondary)
{
	if (secondary) {
		MACIO_OUT32(0x38, save_fcr[2]);
		(void)MACIO_IN32(0x38);
		mdelay(1);
		MACIO_OUT32(0x3c, save_fcr[3]);
		(void)MACIO_IN32(0x38);
		mdelay(10);
		dbdma_restore(macio, save_alt_dbdma);
	} else {
		MACIO_OUT32(0x38, save_fcr[0] | HRW_IOBUS_ENABLE);
		(void)MACIO_IN32(0x38);
		mdelay(1);
		MACIO_OUT32(0x3c, save_fcr[1]);
		(void)MACIO_IN32(0x38);
		mdelay(1);
		MACIO_OUT32(0x34, save_mbcr);
		(void)MACIO_IN32(0x38);
		mdelay(10);
		dbdma_restore(macio, save_dbdma);
	}
}